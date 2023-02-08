#include <stdlib.h>
#include <stdio.h>
#include <string.h>


/*

size t devuelve un valor long unsigned int
snprintf escribe en una estructura char[] lo que se le pasa como string.

Al principio, en otra hay basura sin inicializar que no puede dar errores
    NO ESTÁ VACIA
Para inicializar otra a 0: otra[0] = \0;

*/

enum {
    maxStr = 255,

};

int
main (int argc, char *argv[]) {
    char str[] = "hola";
    char otra[maxStr];

    printf("len: %ld\n", strlen(str));
    snprintf(otra, maxStr, "la string es %s, de tam %ld", str, strlen(str));
    printf("otra vale \"%s\"\n", otra);

    exit(EXIT_SUCCESS);

}