#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>


void
usage(void) {
    fprintf(stderr, "usage: ./defenv [ENV_VAR] PROGRAM_ROUTE\n");
    exit(EXIT_FAILURE);
}


int
main (int argc, char *argv[]) {

    if (argc <= 1)  {
        usage();
    }

    switch (fork()) {
    case -1:
        errx(EXIT_FAILURE, "fork failed!");
    case 0:
        execl("/bin/ls", "ls", NULL);
        break;
    default:
        printf("I am the parent\n");
    }

    return(EXIT_SUCCESS);
}