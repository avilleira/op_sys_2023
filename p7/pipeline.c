#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

enum {
    MAX_LINE = 1024,
    MAX_ARGS = 100,
    PATHS = 2,
    MAX_PIPES = 2,
};


void
usage(void)
{
    fprintf(stderr, "usage: ./pippeline 'COMMAND' 'COMMAND' 'COMMAND'\n");
    exit(EXIT_FAILURE);
}


void
set_arguments(char *cmd_line, char **args) {

    int index;
    char *token;

    index = 0;
    while((token = strtok_r(cmd_line, " ", &cmd_line)) != NULL) {
        args[index] = token;
        index++;
    }
    args[index++] = 0;

}


void
exec_path(char **args)
{

	int i;
	char cmd[MAX_LINE], *paths[PATHS] = { "/bin/", "/usr/bin/" };

	// Considering the order of paths in order to execute the commands.
	for (i = 0; i < PATHS; i++) {
		strcpy(cmd, paths[i]);
		strcat(cmd, args[0]);
		if (access(cmd, F_OK) == 0)
			execv(cmd, args);
	}
	err(EXIT_FAILURE, "exec failed");
}

void
exec_cmd(char *cmd_line)
{
    char *args[MAX_ARGS];

    set_arguments(cmd_line, args);
    exec_path(args);
}


int
main (int argc, char *argv[])
{
    int fd[MAX_PIPES][2], index_cmd, pid, i, sts;

    if (argc != 4)
        usage();

    index_cmd = 0;
    for (i = 1; i < argc; i++) {
        
        if (index_cmd < MAX_PIPES) {
            if (pipe(fd[index_cmd]) < 0)
                err(EXIT_FAILURE, "cannot make a pipe");
        }

        switch ((pid = fork())) {
        case -1:
            err(EXIT_FAILURE, "fork failed");
        case 0:
            if (index_cmd == 0) {
                close(fd[index_cmd][0]);
                close(fd[index_cmd+1][0]);
                close(fd[index_cmd+1][1]);

                if (dup2(fd[index_cmd][1], 1) < 0)
                    err (EXIT_FAILURE, "dup failed");
                close(fd[index_cmd][1]);

                exec_cmd(argv[i]);
            }
            else if (index_cmd == MAX_PIPES) {

                close(fd[index_cmd-1][1]);
                close(fd[index_cmd-2][0]);
                close(fd[index_cmd-2][1]);

                if (dup2(fd[index_cmd-1][0], 0) < 0)
                    err (EXIT_FAILURE, "dup failed");

                close(fd[index_cmd-1][0]);

                exec_cmd(argv[i]);
            }
            else {

                close(fd[index_cmd-1][1]);
                close(fd[index_cmd][0]);

                if (dup2(fd[index_cmd-1][0], 0) < 0)
                    err(EXIT_FAILURE, "dup failed");

                if (dup2(fd[index_cmd][1], 1) < 0)
                    err(EXIT_FAILURE, "dup failed");

                close(fd[index_cmd-1][0]);
                close(fd[index_cmd][1]);

                exec_cmd(argv[i]);
            }     

            break;
        default:

            break;
        }

        index_cmd++;
    }

    while ((pid = wait(&sts)) != -1) {
		if (WIFEXITED(sts))
		    return (WEXITSTATUS(sts));
	}

    return EXIT_SUCCESS;
}