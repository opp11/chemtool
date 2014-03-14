#include "db_read.h"

static const char* db_name = "elemdb.csv";
static char db_path[BUFSIZ] = "./elemdb.csv";

//Fills out the data fields of a single pe_elem struct
//by reading from the 'elemdb' file
static int get_single_data(struct pe_elem *elm, FILE *elemdb);

//Walks DOWN through the file 'elemdb' untill it reaches a mathcing name or EOF
static int walk_to_elem(char name[4], FILE *elemdb);

//Walks to the next line in the file 'f' and then 'offset' chars to the right
static void to_next_line(FILE *f, int offset);

//Values should be seperated by a semicolon. This returns 0 if we are on a
//semicolon now. If we are not it prints an error message and returns EDBFMT.
//Also moves 1 char forward in the file.
static int conf_septor(FILE *f);

int get_elem_data(struct elem_vec *evec)
{
	FILE *elemdb = NULL;
	int i = 0;
	int err = 0;

	elemdb = fopen(db_path, "r");
	//abort on failure to open
	if (!elemdb){
		print_err(EDBOPEN, db_path);
		//direct return to avoid call to fclose
		return EDBOPEN;
	}

	//get the data for all elements
	for (; i < evec->size; i++){
		err = get_single_data(&evec->elms[i], elemdb);
		
		//abort if an error was returned
		if (err)
			goto exit;
	}

exit:
	fclose(elemdb);
	return err;
}

int set_db_path(const char* path)
{
	int len = strlen(path);
	char new_dir[BUFSIZ] = {0};

	while (len && path[len] != '/' && path[len] != '\\'){
		len--;
	}
	if (!len){
		strcpy(new_dir, "./");
	} else if (len + strlen(db_name) + 1 < BUFSIZ){
		//copy the first 'len' chars of len as the new dir
		strncpy(new_dir, path, len);
	} else {
		//return error if the path is too large
		return len;
	}
	sprintf(db_path, "%s/%s", new_dir, db_name);

	return 0;
}

static int get_single_data(struct pe_elem *elm, FILE *elemdb)
{
	int err = 0;

	err = walk_to_elem(elm->sname, elemdb);
	if (err){
		return err;
	}

	err = conf_septor(elemdb);
	if (err)
		return err;

	//read element weight
	err = fscanf(elemdb, "%lf", &elm->weight);
	//fscanf returns 0 or EOF on read failure so check for that
	if (!err || err == EOF){
		print_err(EDBFMT, "could not read an element's weight.");
		return EDBFMT;
	}

	err = conf_septor(elemdb);
	if (err)
		return err;

	//read full name of the element
	err = fscanf(elemdb, "%[^;]", elm->lname);
	if (!err || err == EOF){
		print_err(EDBFMT, "could not read an element's full name.");
		return EDBFMT;
	}

	return 0;
}

static int walk_to_elem(char name[4], FILE *elemdb)
{
	char raw[4] = {0, 0, 0, 0};
	int did_rewind = 0;
	char* resp;

	resp = fgets(raw, 4, elemdb);
	//walk untill the names match
	while (strncmp(name, raw, 3)){
		to_next_line(elemdb, 0);
		if (!resp){
			if (!did_rewind){
				rewind(elemdb);
				did_rewind = 1;
			} else { 
				//this is the second time we have walked the 
				//whole file, so abort and print err message.
				print_err(EENAME, name);
				return EENAME;
			}
		}
		resp = fgets(raw, 4, elemdb);
	}

	return 0;
}

static void to_next_line(FILE *f, int offset)
{
	char crnt;
	//walk to next line or end of file
	do {
		crnt = fgetc(f);
	} while (crnt != '\n' && crnt != EOF);
	
	//walk to offset
	if (crnt != EOF){
		while (offset--)
			fgetc(f);
	}
}

static int conf_septor(FILE *f)
{
	if (fgetc(f) != ';'){
		print_err(EDBFMT, "missing a seperating semicolon.");
		return EDBFMT;
	}
	return 0;
}