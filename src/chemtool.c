#include "chemtool.h"

int get_weight(int elm_count, struct elem *elm_vec)
{
	FILE *elemdb = NULL;
	elemdb = fopen("./elemdb.csv", "r");
	//abort on failure to open
	if (!elemdb)
		return -1;

	
	
	fclose(elemdb);
	return 0;
}

void to_next_line(FILE *f)
{
	char crnt;
	do {
		crnt = fgetc(f);
	} while (crnt != '\n' && crnt != EOF);
}
