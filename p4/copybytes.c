#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <err.h>

// Author: Jaime Avilleira García
// File: copybytes.c

enum {
	MAX_LECTURE = 100
};

void
usage(void)
{
	fprintf(stderr, "usage: ./copybytes origin dest [N]\n");
	exit(EXIT_FAILURE);
}

int
is_a_number(char *number)
{

	if ((atoi(number) == 0) && (strcmp(number, "0") != 0))
		return 0;
	else
		return 1;
}

void
read_write(char *orig, char *dest, int bytes)
{

	char buffer[MAX_LECTURE];
	int fd_orig, fd_dest, nr, b_count;

	if (!strcmp(orig, "-"))
		fd_orig = 1;
	else {
		if ((fd_orig = open(orig, O_RDONLY | O_CREAT, 0666)) < 0)
			err(EXIT_FAILURE, "open failed.");
	}

	if (!strcmp(dest, "-"))
		fd_dest = 0;
	else {
		if ((fd_dest =
		     open(dest, O_WRONLY | O_CREAT | O_TRUNC | O_APPEND,
			  0666)) < 0)
			err(EXIT_FAILURE, "open failed.");
	}

	if (bytes < 0) {	// Full read and write from a file
		while ((nr = read(fd_orig, buffer, MAX_LECTURE)) != 0) {
			if (nr < 0)
				err(EXIT_FAILURE, "read failed.");

			if (write(fd_dest, buffer, nr) == -1)
				err(EXIT_FAILURE, "write failed.");
		}
	}

	else {
		b_count = 0;

		while (((nr = read(fd_orig, buffer, 1)) != 0)
		       && (bytes > b_count)) {
			if (nr < 0)
				err(EXIT_FAILURE, "read failed.");
			b_count += nr;
			if (write(fd_dest, buffer, nr) == -1)
				err(EXIT_FAILURE, "write failed.");
		}
	}

	close(fd_orig);
	close(fd_dest);
}

int
main(int argc, char *argv[])
{

	int bytes;

	if (argc < 3 || argc > 4)
		usage();

	if ((argc == 4) && (is_a_number(argv[3])))
		bytes = atoi(argv[3]);
	else if (argc < 4)
		bytes = -1;	// When bytes are not specified in the params.
	else
		usage();

	read_write(argv[1], argv[2], bytes);

	return EXIT_SUCCESS;
}
