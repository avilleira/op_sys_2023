#include <stdio.h>
#include <stdlib.h>
#include "listcreat.h"

// Print all the characteristics of the creature.
void
print_creat(Creat* creat) {

    printf("ID: %Ld\n", creat->id);
    printf("SPECIE: %s\n", creat->specie);
    printf("HEIGHT: %d\n", creat->height);
    printf("WEIGHT: %d\n", creat->weight);
    printf("COLOR: %s\n", creat->color);
}

// All methods for the List

List*
create_list(void) {
    List* creatures;
    creatures = malloc(sizeof(List));
    creatures->n_creatures = 0;
    return creatures;
}

int
is_empty(List* list) {

    if (list->n_creatures == 0)
        return 1;
    else
        return 0;
}

void
add_creature_top (Creat* creat, List* list) {

    Creat* aux;
    if (list->n_creatures == 0) {
        list->first = malloc(sizeof(Creat));
        list->first = creat;
    }
}