
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

/*
    NULL = (void *) 0 ---> Puntero a cualquier cosa. Se utilizan para funciones que reservan memoria.

    En las structs:
        - typedef struct Coordenada para definir un tipo Coordenada.
        - Si hay un puntero a coordenada:
            Coordenada *pc;
            Coordenada c;
            pc = &c;
            c.v = 3;
            (*pc).x = 3 ===== pc->x = 3;

    Memoria dinámica:
        Importante para que tu programa pueda seguir utilizando la memoria. Liberar en cuanto se deja de usar.
            Coordenada *pc;
            pc = (Coordenada)malloc(sizeof(Coordenada));
            free(pc);
            pc = NULL; ----> Asegurarse de que nadie lo puede utilizar.
            free(pc); ----> Liberar dos veces, el programa casca.
        Toda la memoria global sin inicializar (variable global sin inicializar: memoria cuyo ámbito es todo el fichero desde donde se declara) se obtiene desde heap.

*/
int
main (int argc, char **argv){
    char **p; 
    //Forma de recorrer un puntero de punteros.
    for(p = argv; *p != NULL; p++)
        printf("argv %s\n", *p);
    exit(EXIT_SUCCESS);
}