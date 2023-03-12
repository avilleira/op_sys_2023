#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void
usage(void) {
    fprintf(stderr, "usage: pinger N machine1 [machines ...]\n" );
    exit(EXIT_FAILURE);
}

int is_a_number(char *number) {

    if ((atoi(number) == 0) && (strcmp(number, "0") != 0))
        return 0;
    else
        return 1;
}

int main (int argc, char *argv[]){
    
    int deadline, pid;

    if (argc < 3) {
        usage();
    }
    
    if (is_a_number(argv[1]))
        deadline = atoi(argv[1]);
    else
        usage();

    return EXIT_SUCCESS;
}