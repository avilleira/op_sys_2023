#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

// Checking if the list is empty.
int
is_empty(List* list) {

    if (list->n_creatures == 0)
        return 1;
    else
        return 0;
}

void
copy_elements (Creat* src, Creat* dest) {
    dest->id = src->id;
    dest->color = src->color;
    dest->specie = src->specie;
    dest->height = src->height;
    dest->weight = src->weight;
}

// Adding elements at the top of the list.
void
add_creature_top(Creat *creat, List *list) {
    Creat* new_creat;
    new_creat = malloc(sizeof(Creat));

    copy_elements(creat, new_creat);

    if (is_empty(list)) {
        list->first = new_creat;
        list->last = new_creat;
    }
    else{
        new_creat->next = list->first;
        list->first->prev = new_creat;
        list->first = new_creat;
    }
    list->n_creatures++;
}

// Adding elements at the end of the list.
void
add_creature_end(Creat *creat, List *list) {
    Creat* new_creat;
    new_creat = malloc(sizeof(Creat));  
    copy_elements(creat, new_creat);    
    if (is_empty(list)) {
        list->first = new_creat;
        list->last = new_creat;
    }
    else{
        new_creat->prev = list->last;
        list->last->next = new_creat;
        list->last = new_creat;
    }
    list->n_creatures++;
}

// Determining first creature
void
print_first(List *list) {
    print_creat(list->first);
}

// Determining last creature
void
print_last(List *list) {
    print_creat(list->last);
}

// Asking n creatures of the list
int
count_creature(List *list) {
    return list->n_creatures;
}

// Asking if the animal is in the list
Creat
*is_creature(List *list, long long id) {
    int index;
    Creat *tmp;
    tmp = list->first;

    for (index = 0; index < list->n_creatures; index++) {
        if (id != tmp->id)
            tmp = tmp->next;
        else
            return tmp;
        
        if (tmp->next == NULL)
            return 0;
    }
    return 0;
}

// Delete a creature
void
del_creature (List *list, Creat* creat) {

    if (creat->prev != NULL)
        creat->prev->next = creat->next;
    if (creat->next != NULL)
        creat->next->prev = creat->prev;

    free(creat);
    list->n_creatures--;
}

// Delete List
void 
del_list (List *list) {
    Creat *tmp, *next;

    if (list == NULL)
        return;
        
    for (tmp = list->first; tmp !=NULL; tmp = next) {
        next = tmp->next;
        free(tmp);
    }
    free(list);
}