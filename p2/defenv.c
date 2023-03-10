#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <err.h>

void
usage(void)
{
	fprintf(stderr, "usage: ./defenv [ENV_VAR] PROGRAM_ROUTE\n");
	exit(EXIT_FAILURE);
}

//Get the var from the argv string.
char *
get_var(char *str, char del)
{
	char *var;
	int index;

	var = malloc(sizeof(char *));
	strcpy(var, str);

	for (index = 0; index < strlen(var); index++) {
		if (var[index] == del) {
			var[index] = '\0';
			break;
		}
	}
	return var;
}

// Create an array with all the arguments needed for the execv call.
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
son_behavior(int argc, char **args)
{

	int i;
	char wanted_char, *var, *value, *exec_args[argc];

	wanted_char = '=';

	for (i = 1; i < argc; i++) {
		if ((value = strchr(args[i], wanted_char)) != NULL) {
			value = value + 1;
			var = get_var(args[i], '=');
			if (setenv(var, value, 1) != 0) {
				warnx("setenv has failed. %s has not been set",
				      var);
			}
			free(var);
		} else {	//We put a break here to avoid the for loop continue.
			break;
		}
	}

	set_arguments(i, exec_args, args, argc);
	execv(exec_args[0], exec_args);
	// In case execv failed:
	err(EXIT_FAILURE, "execv failed");
}

int
main(int argc, char *argv[])
{

	int pid, sts;

	if (argc <= 1)
		usage();

	pid = fork();
	switch (pid) {
	case -1:
		errx(EXIT_FAILURE, "fork failed!");
	case 0:
		son_behavior(argc, argv);
		break;
	default:
		while ((pid = wait(&sts)) != -1) {
			if (WIFEXITED(sts))
				return (WEXITSTATUS(sts));
		}
	}
	return EXIT_SUCCESS;
}
