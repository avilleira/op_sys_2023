#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "listcreat.h"

enum {
	Nthreads = 100,
};

void
usage(void)
{
	fprintf(stderr, "Usage: ./main\n");
	exit(EXIT_FAILURE);
}

int
main(int argc, char *argv[])
{
	if (argc != 1)
		usage();

	List *creature_list;
	pthread_t thread[Nthreads];
	int i;

	creature_list = create_list();

	for (i = 0; i < Nthreads; i++) {
		if (pthread_create(&thread[i], NULL, NULL, NULL) != 0) {
			warnx("error creating thread");
			return EXIT_FAILURE;
		}
	}
}
