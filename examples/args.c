
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

/*
    NULL = (void *) 0 ---> Puntero a cualquier cosa. Se utilizan para funciones que reservan memoria.
*/
int
main (int argc, char **argv){
    char **p; 
    //Forma de recorrer un puntero de punteros.
    for(p = argv; *p != NULL; p++)
        printf("argv %s\n", *p);
    exit(EXIT_SUCCESS);
}