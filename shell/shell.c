#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

enum {
    MAX_LINE = 1024,
    MAX_PIPES = 100,
    MAX_ARGS = 100,
    PATHS = 2,
};

void
usage (void) {
    fprintf(stderr, "usage: ./shell\n");
    exit(EXIT_FAILURE);
}

int
tokenize_line (char *line, char *delim, char **token_line) {
    int index;
	char *token;

	index = 0;
	while ((token = strtok_r(line, delim, &line)) != NULL)
		token_line[index++] = token;

    return index;
}

void
close_fd (int fd[MAX_PIPES][2], int pipes, int used) { // Will close all the fd except the one it receives as argument
    int i;
    for (i = 0; i < pipes; i++) {
        if (i != used) {
            close(fd[i][0]);
            close(fd[i][1]);
        }
    }
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
    fprintf(stderr, "error: cmd %s not founded\n", args[0]);
    exit(EXIT_FAILURE);
	err(EXIT_FAILURE, "exec failed");
}

void
cd_builtin(char *path) {
    
    if(strcmp(path, "") == 0)
        chdir("/home");
    else if (chdir(path) != 0) {
        fprintf(stderr, "cd failed: No such file or directory\n");
        exit(1);
    }
}

void
exec_cmd (char *cmd_line) {

    char *args[MAX_ARGS];
    int n_args;
    n_args = tokenize_line(cmd_line, " ", args);
    
    // Deciding if it is a builtin:
    if (!strcmp("cd", args[0])) {
        cd_builtin(args[1]);
    }
    else { 
        args[n_args++] = 0;
        exec_path(args);
    }
}


int
main (int argc, char *argv[]) {
    
    int pid, pipes, sts, index_cmd, fd[199][2];
    char line_read[MAX_LINE], *line, *cmd_arr[MAX_ARGS];

    if (argc != 1)
        usage();
    while (fgets(line_read, MAX_LINE, stdin) != NULL) {

        // In case that the line is empty
        if (!strcmp(line_read, "\n"))
            continue;
        
        line = strtok(line_read, "\n");
        pipes = tokenize_line(line, "|", cmd_arr)-1;
        for (index_cmd = 0; index_cmd <= pipes; index_cmd++) {
            if (index_cmd < pipes) {
                if (pipe(fd[index_cmd]) < 0)
                    err(EXIT_FAILURE, "cannot make a pipe");
            }
            switch ((pid = fork())) {
                case -1:
                    err(EXIT_FAILURE, "fork failed");
                case 0:
                    if (pipes == 0) {
                        exec_cmd(cmd_arr[0]);
                    }
                    else if (index_cmd == 0) {
                        close(fd[0][0]);
                        if (dup2(fd[0][1], 1) < 0)
	                	    err(EXIT_FAILURE, "dup failed");
	                	close(fd[0][1]);
                        exec_cmd(cmd_arr[0]);
                    }
                    else if (index_cmd == pipes) {
                        fprintf(stderr, "stderr\n");
                        close (fd[1-1][1]);
	                	if (dup2(0, 0) < 0)
	                		err(EXIT_FAILURE, "dup failed");
                        close(fd[1-1][0]);	                	
                        exec_cmd(cmd_arr[1]);
                        
                    }
                    break;
                default:
                    break;
            }
            while ((pid = wait(&sts)) != -1) {
		    if (WIFEXITED(sts))
		    	continue;
	        }
        }
    }
    return EXIT_SUCCESS;
}