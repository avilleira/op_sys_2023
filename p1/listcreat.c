#include <stdio.h>
#include <stdlib.h>
#include "listcreat.h"


// Print all the characteristics of the creature.
void
print_creat(struct Creat Creat) {

    printf("ID: %Ld\n", Creat.id);
    printf("SPECIE: %s\n", Creat.specie);
    printf("HEIGHT: %d\n", Creat.height);
    printf("WEIGHT: %d\n", Creat.weight);
    printf("COLOR: %s\n", Creat.color);
}

// All methods for the List

struct Creat*
create_list() {
    struct Creat* creat_list;
    creat_list = NULL;
    return creat_list;
}

int
is_empty(struct Creat* list) {
    if (list == NULL)
        return 0;
    else
        return 1;
}