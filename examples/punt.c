#include <stdlib.h>
#include <stdio.h>

int
main (int argc, char *argv[]) {

    int i, *p;

    i = 3;
    p = &i;
    p += 1;

    printf("la direccion de i es %p\n", &i);
    printf("la direccion contenida en p es %p\n", p);
    printf("el valor de *p es %d\n", *p);

    exit(EXIT_SUCCESS);


}