#include <stdlib.h>
#include <stdio.h>
#include <string.h>


/*
ARRAYS DE DOS DIMENSIONES:
    - 

Pasar variable por referencia: Pasarle un puntero a una funcion de esa  variable.

El string acaba donde pones el \0
------------
char *str = "hola"; Iniciada una posición de memoria de solo lectura
str[0] = '\0'; No se puede escribir en solo lectura.
str = "adios"; Asinga a la variable str "adios"
------------
char str[] = "hola";
str = "adios"; No se puede, no se puede cambiar una estructura inmutable.
------------


*/

enum {
    MaxN = 32,
};

void
duparray(int *ar){
    int i;
    for (i = 0; i <  MaxN; i++){
        ar[MaxN] = 2*ar[MaxN];
    }
}

void
printarray(int *ar){
    int i;
    for (i = 0; i < MaxN; i++){
        printf("ar[%d] = %d\n", i, ar[i]);
    }
}

int
main (int argc, char *argv[]) {
    int i,ar[MaxN];
    
    //memset(ar, 3, MaxN*sizeof(int)); Inicializa bytes en esa posicion de memoria, no asigna valores.

    for (i = 0; i < MaxN; i++)
        ar[i] = 3;

    printarray(ar);
    duparray(ar);
    printarray(ar);

    exit(EXIT_SUCCESS);

}