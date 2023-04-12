#include <stdio.h>
#include <stdlib.h>

void
usage (void)
{
    fprintf(stderr, "usage: ./pippeline 'COMMAND' 'COMMAND' 'COMMAND'\n");
    exit(EXIT_FAILURE);
}


int
main (int argc, char *argv[])
{
    if (argc != 4)
        usage();
    return EXIT_SUCCESS;
}