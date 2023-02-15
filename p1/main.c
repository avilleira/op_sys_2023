#include <stdlib.h>
#include <stdio.h>
#include "listcreat.h"

void
usage(void) {
    fprintf(stderr, "Usage: ./main\n");
    exit(EXIT_FAILURE);
}

int
main (int argc, char *argv[]) {
    if (argc != 1)
        usage();
    List* creature_list;
    creature_list = create_list();
    printf("III:%d\n", is_empty(creature_list));
    exit(EXIT_SUCCESS);
}