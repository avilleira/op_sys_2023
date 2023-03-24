#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <err.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <dirent.h>

enum {
    MAX_LINE=256,
};
void
usage (void) {
    fprintf(stderr, "usage: ./sourcefiles.c PATH ...\n");
    exit(EXIT_FAILURE);
}

void
read_dir_recurs (DIR *d) {

}

// Para  buscar ficheros .c y .h strrchr.
int
main (int argc, char *argv[]) {

    int i;
    char line[MAX_LINE];
    DIR *d;
    while (fgets(line, MAX_LINE, stdin) != NULL) {
        opendir(line);
    }

    
    return EXIT_SUCCESS;
}