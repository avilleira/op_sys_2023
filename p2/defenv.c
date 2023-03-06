#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <err.h>



void
usage(void) {
    fprintf(stderr, "usage: ./defenv [ENV_VAR] PROGRAM_ROUTE\n");
    exit(EXIT_FAILURE);
}


char *
get_var (char *str, char del) {
    char *var;
    int index;

    var = malloc(sizeof(char*));
    strcpy(var, str);

    for (index = 0; index < strlen(var); index++) {
        if (var[index] == del) {
            var[index] = '\0';
            break;
        }
    }
    return var;
}


void
son_behavior( int argc, char **args) {
    int i;
    char wanted_char, *var, *value, *filename;
    
    wanted_char = '=';

    for (i = 1; i < argc; i++) {
        if ((value = strchr(args[i], wanted_char)) != NULL){
            value = value+1;
            var = get_var(args[i], '=');
            if (setenv(var, value, 1) != 0) {
                warnx("setenv has failed. %s has not been set.", var);
            }
            free(var);
        }
        else {
            fprintf(stderr, "No más variables\n");
            break;
        }
    }

    filename = strrchr(args[i], '/');
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