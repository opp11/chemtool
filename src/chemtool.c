#include "chemtool.h"

int get_elem_weights(int elm_count, struct pe_elem *elm_vec)
{
	FILE *elemdb = NULL;

	elemdb = fopen("./elemdb.csv", "r");
	//abort on failure to open
	if (!elemdb)
		return -1;

	
	
	fclose(elemdb);
	return 0;
}

int get_weight(struct pe_elem *elm, FILE *elemdb)
{
	walk_to_elem(elm->name, elemdb);

	//We should be on a space right now, so check that.
	//We also need to advance 1 anyway, so 'fgetc' also accomplishes that.
	if (fgetc(elemdb) != ' ')
		return -1;

	

	return 0;
}

void walk_to_elem(char name[3], FILE *elemdb)
{
	int i = 0;

	//Walk down the file untill we have matched all of 'name'.
	//Since everything should be ordered alphabetically, 
	//we do not have to consider whether we are already past the target.
	while (name[i]){
		while (name[i] != fgetc(elemdb))
			to_next_line(elemdb, i);

		i++;
	}
}

void to_next_line(FILE *f, int offset)
{
	char crnti;
	do {
		crnt = fgetc(f);
	} while (crnt != '\n' && crnt != EOF);
	
	if (crnt != EOF){
		while (offset--)
			fgetc(f);
	}
}
