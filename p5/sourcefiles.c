#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <err.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

enum {
	MAX_LINE = 1024,
	C_FILE = 1,
	H_FILE = 2,
};

struct Directory {
	char *path;
	int cfiles;
	int hfiles;
	long bytes;
	int exit_status;
};
typedef struct Directory Directory;

void
usage(void)
{
	fprintf(stderr, "usage: ./sourcefiles.c PATH ...\n");
	exit(EXIT_FAILURE);
}

int
is_c_or_h(char *file)
{
	char *ptr;

	if ((ptr = strrchr(file, '.')) != NULL) {
		if (!strcmp(ptr, ".c"))
			return 1;
		else if (!strcmp(ptr, ".h"))
			return 2;
	}
	return 0;
}

int
is_a_dir(char *path)
{

	struct stat st;

	if (stat(path, &st) < 0)
		err(EXIT_FAILURE, "stat failed");

	if ((st.st_mode & S_IFMT) == S_IFDIR)
		return 1;
	return 0;
}

void
add_elements(Directory *elems, char *path, int f_type)
{

	struct stat st;

	if (access(path, R_OK) == -1) {
		elems->exit_status = 1;
		warn("Error in %s", path);
	}

	if (stat(path, &st) < 0)
		err(EXIT_FAILURE, "stat failed");

	elems->bytes += st.st_size;
	if (f_type == C_FILE)
		elems->cfiles += 1;
	else if (f_type == H_FILE)
		elems->hfiles += 1;
}

// Recursive method to detect all the .c and .h files
Directory
read_dir_recurs(char *path)
{

	DIR *d;
	struct dirent *ent;
	Directory dir, dir_son;
	char *elem_path;

	dir.bytes = 0;
	dir.cfiles = 0;
	dir.hfiles = 0;
	dir.exit_status = 0;

	strcat(path, "/");

	if ((d = opendir(path)) == NULL) {
		dir.exit_status = 1;
		warn("error in %s", path);
		return dir;
	}

	elem_path = malloc(sizeof(char *) * MAX_LINE);

	dir.path = elem_path;
	while ((ent = readdir(d)) != NULL) {
		if (ent->d_name[0] != '.') {
			strcpy(elem_path, path);
			strcat(elem_path, ent->d_name);
			if (is_a_dir(elem_path)) {
				dir_son = read_dir_recurs(elem_path);
				dir.bytes += dir_son.bytes;
				dir.cfiles += dir_son.cfiles;
				dir.hfiles += dir_son.hfiles;
				if (dir_son.exit_status == 1)
					dir.exit_status = 1;
			}

			if (is_c_or_h(elem_path) == C_FILE)
				add_elements(&dir, elem_path, C_FILE);
			else if (is_c_or_h(elem_path) == H_FILE)
				add_elements(&dir, elem_path, H_FILE);
		}
	}
	closedir(d);
	free(elem_path);
	return dir;

}

int
main(int argc, char *argv[])
{

	char line_max[MAX_LINE], *line;
	Directory directory;

	while (fgets(line_max, MAX_LINE, stdin) != NULL) {
		line = strtok(line_max, "\n");
		directory = read_dir_recurs(line);
		if (!directory.exit_status)
			printf("%s   %d  %d %ld\n", line, directory.cfiles,
			       directory.hfiles, directory.bytes);
	}

	return EXIT_SUCCESS;
}
