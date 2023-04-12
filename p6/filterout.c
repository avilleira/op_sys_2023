#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

enum {
	MAX_LINE = 1024,
	PATHS = 2,
};

void
usage(void)
{
	fprintf(stderr, "usage: ./filterout REGEXP CMD [args]...\n");
	exit(EXIT_FAILURE);
}

void
set_arguments(int index, char **dest, char **src, int argc)
{

	int src_i, dest_i;

	dest_i = 0;

	for (src_i = index; src_i < argc; src_i++) {
		dest[dest_i] = src[src_i];
		dest_i++;
	}
	// We add  a zero at the end to make a NULL pointer in the end of the args array.
	dest[dest_i] = 0;
}

void
exec_path(char **args)
{

	int i;
	char cmd[MAX_LINE], *paths[PATHS] = { "/bin/", "/usr/bin" };

	// Respecting the order of paths in order to execute the commands.
	for (i = 0; i < PATHS; i++) {
		strcpy(cmd, paths[i]);
		strcat(cmd, args[0]);
		if (access(cmd, F_OK) == 0)
			execv(cmd, args);
	}
	err(EXIT_FAILURE, "exec failed");
}

void
exec_command(int n_args, char **args)
{

	char *exec_args[n_args];

	set_arguments(2, exec_args, args, n_args);
	exec_path(exec_args);

}

int
main(int argc, char *argv[])
{
	int sts, pid, fd[2];

	if (argc < 3)
		usage();

	if (pipe(fd) < 0)
		err(EXIT_FAILURE, "cannot make a pipe");

	switch (fork()) {
	case -1:
		err(EXIT_FAILURE, "fork failed");
	case 0:
		close(fd[0]);
		if (dup2(fd[1], 1) < 0)
			err(EXIT_FAILURE, "dup failed");
		close(fd[1]);
		exec_command(argc, argv);
	default:
		pid = fork();
		switch (pid) {
		case -1:
			err(EXIT_FAILURE, "fork failed");
		case 0:
			close(fd[1]);
			if (dup2(fd[0], 0) < 0)
				err(EXIT_FAILURE, "dup failed");
			close(fd[0]);
			execl("/usr/bin/egrep", "egrep", argv[1], NULL);
			err(EXIT_FAILURE, "exec_failed");
		default:
			while ((pid = wait(&sts)) != -1) {
				if (WIFEXITED(sts))
					return (WEXITSTATUS(sts));
			}
		}
	}
	return WEXITSTATUS(sts);

}
