#include <stdlib.h>
#include <stdio.h>
#include "listcreat.h"

void
usage(void)
{
	fprintf(stderr, "Usage: ./main\n");
	exit(EXIT_FAILURE);
}

Creat creatures[] = {
	{1, "meerkat", "brown", 300, 730, NULL, NULL},
	{2, "zarigüeya", "grey", 700, 6000, NULL, NULL},
	{3, "dog", "white", 250, 4000, NULL, NULL},
	{4, "cat", "black", 240, 6000, NULL, NULL},
	{5, "parakeet", "yellow", 190, 35, NULL, NULL},
	{6, "mole", "brown", 200, 550, NULL, NULL},
	{7, "eagle", "brown", 950, 7000, NULL, NULL},
	{8, "dolphin", "grey", 2700, 140000, NULL, NULL},
	{9, "horse", "white", 1700, 420000, NULL, NULL},
	{10, "ostrich", "black", 3000, 180000, NULL, NULL}
};

int
main(int argc, char *argv[])
{
	if (argc != 1)
		usage();
	List *creature_list;

	creature_list = create_list();
	add_creature_top(&creatures[0], creature_list);
	exit(EXIT_SUCCESS);
}
