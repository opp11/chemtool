#include "db_read.h"

//Fills out the data fields of a single pe_elem struct
//by reading from the 'elemdb' file
static int get_data(struct pe_elem *elm, FILE *elemdb);

//Walks DOWN through the file 'elemdb' untill it reaches a mathcing name or EOF
static int walk_to_elem(char name[3], FILE *elemdb);

//Extracts the data from the current line of 'elemdb' and stores it in 'elm'
static void extract_data(struct pe_elem *elm, FILE *elemdb);

//Walks to the next line in the file 'f' and then 'offset' chars to the right
static void to_next_line(FILE *f, int offset);

int get_elem_weights(int elm_count, struct pe_elem *elm_vec)
{
	FILE *elemdb = NULL;
	int i = 0;
	int err = 0;

	elemdb = fopen("./elemdb.csv", "r");
	//abort on failure to open
	if (!elemdb){
		return EFOPEN;
	}

	for (; i < elm_count; i++){
		err = get_data(&elm_vec[i], elemdb);
		
		//abort if an error was returned
		if (err)
			break;
	}

	fclose(elemdb);
	return err;
}

static int get_data(struct pe_elem *elm, FILE *elemdb)
{
	if (walk_to_elem(elm->name, elemdb))
		return EENAME;

	//We should be on a semicolon right now, so check that.
	//We also need to advance 1 anyway, so 'fgetc' also accomplishes that.
	if (fgetc(elemdb) != ';')
		return EFORMAT;

	extract_data(elm, elemdb);

	return 0;
}

static int walk_to_elem(char name[3], FILE *elemdb)
{
	char raw[4] = {0, 0, 0, 0};
	char* resp;

	resp = fgets(raw, 4, elemdb);
	//walk untill the names match
	while (raw[0] != name[0] || raw[1] != name[1] || raw[2] != name[2]){
		if (!resp)
			//abort if there is a read error
			//this is most likely due to reaching EOF
			return EENAME;
		to_next_line(elemdb, 0);
		resp = fgets(raw, 4, elemdb);
	}

	return 0;
}

static void extract_data(struct pe_elem *elm, FILE *elemdb)
{
	char raw[13];
	fgets(raw, 13, elemdb);
	elm->weight = strtod(raw, NULL);
}

static void to_next_line(FILE *f, int offset)
{
	char crnt;
	//walk to next line
	do {
		crnt = fgetc(f);
	} while (crnt != '\n' && crnt != EOF);
	
	//walk to offset
	if (crnt != EOF){
		while (offset--)
			fgetc(f);
	}
}
