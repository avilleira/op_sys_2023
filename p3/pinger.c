#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <err.h>

void
usage(void)
{
	fprintf(stderr, "usage: pinger N machine1 [machines ...]\n");
	exit(EXIT_FAILURE);
}

int
is_a_number(char *number)
{

	if ((atoi(number) == 0) && (strcmp(number, "0") != 0))
		return 0;
	else
		return 1;
}

void
son_behavior(char *machine, char *deadline)
{
	execl("/usr/bin/ping", "ping", "-q", "-c", "2", "-w", deadline, machine,
	      NULL);
	err(EXIT_FAILURE, "execl failed");
}

// Function to control the different msgs that will produce the different son's states.
int
error_handler(int sts, char *machine, int exit_value)
{

	int exit_val;

	if (WEXITSTATUS(sts)) {
		fprintf(stderr, "no está disponible o encencida: %s\n",
			machine);
		exit_val = 1;
	} else if (WEXITSTATUS(sts) == 2) {
		fprintf(stderr, "no existe: %s\n", machine);
		exit_val = 1;
	} else
		exit_val = 0;

	return exit_val;
}

int
main(int argc, char *argv[])
{

	int pid, sts, i, exit_value;
	char *deadline;

	if (argc < 3) {
		usage();
	}

	if (is_a_number(argv[1]))
		deadline = argv[1];
	else
		usage();

	for (i = 2; i < argc; i++) {
		pid = fork();
		switch (pid) {
		case -1:
			errx(EXIT_FAILURE, "fork failed!");
		case 0:
			son_behavior(argv[i], deadline);
			break;
		}
		while ((pid = wait(&sts)) != -1) {
			if (WIFEXITED(sts)) {
				exit_value =
				    error_handler(sts, argv[i + 2], exit_value);
			}
		}
	}
	// Returning the state value that the son proccess has finished with.
	return exit_value;
}
