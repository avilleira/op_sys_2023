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

void
son_behavior( int argc, char **args) {
    int i;
    for (i = 1; i < argc; i++) {
        //AQUI VA LO DEL STRCHR
    }
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
        son_behavior(argc, argv);
        break;
    default:
        printf("I am the parent\n");
    }

    return(EXIT_SUCCESS);
}