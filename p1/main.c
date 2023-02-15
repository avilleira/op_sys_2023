#include <stdlib.h>
#include <stdio.h>
#include "listcreat.h"

void
usage() {
    fprintf(stderr, "Usage: ./main\n");
    exit(EXIT_FAILURE);
}

int
main (int argc, char *argv[]) {
    if (argc != 1)
        usage();
    struct Creat* Creat;
    Creat = create_list();
    printf("III:%d\n", is_empty(Creat));
    exit(EXIT_SUCCESS);
}