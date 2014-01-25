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

	extract_data(elm, elemdb);

	return 0;
}

int walk_to_elem(char name[3], FILE *elemdb)
{
	char raw[4] = {0, 0, 0, 0};
	char* resp;

	resp = fgets(raw, 4, elemdb);
	while (raw[0] != name[0] || raw[1] != name[1] || raw[2] != name[2]){
		if (!resp)
			//abort if there is a read error
			return -1;
		to_next_line(elemdb, 0);
		resp = fgets(raw, 4, elemdb);
	}

	return 0;
}

void extract_data(struct pe_elem *elm, FILE *elemdb)
{
	char raw[14];
	char crnt = fgetc(elemdb);
	int i = 0;

	//extract the weight
	while (crnt != ' '){
		raw[i] = crnt;
		i++;
		crnt = fgetc(elemdb);
	}
	//pad the rest of raw with zeroes
	while (i < 14){
		raw[i] = '0';
		i++;
	}

	elm->weight = strtof(raw, NULL);
}

void to_next_line(FILE *f, int offset)
{
	char crnt;
	do {
		crnt = fgetc(f);
	} while (crnt != '\n' && crnt != EOF);
	
	if (crnt != EOF){
		while (offset--)
			fgetc(f);
	}
}
