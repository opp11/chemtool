#include "db_read.h"

#define MAX_PATH_LEN 8192
#define DB_NAME_LEN strlen(db_name)

static const char* db_name = "elemdb.csv";
static char db_path[MAX_PATH_LEN] = "./elemdb.csv";

/*
 *Fills out the data fields of a single pe_elem struct
 *by reading from the 'elemdb' file
 */
static int get_single_data(struct pe_elem *elm, FILE *elemdb);

/* Walks through the file 'elemdb' untill it reaches a mathcing name or EOF */
static int walk_to_elem(char name[4], FILE *elemdb);

/* Walks to the next line in the file 'f' and 'offset' chars to the right */
static void to_next_line(FILE *f, int offset);

/*
 *Converts a string to a double. We make our own since the
 *normal C string conversion functions round the numbers down too
 *aggressively e.g. 4.002 gets rounded to 4.0
 */
static double str_to_double(char* str);

/*
 *Values should be seperated by a semicolon. This returns 0 if we are on a
 *semicolon now. If we are not it prints an error message and returns EDBFMT.
 *Also moves 1 char forward in the file.
 */
static int confirm_seperator(FILE *f);

int get_elem_data(struct elem_vec *evec)
{
	FILE *elemdb = NULL;
	int i = 0;
	int err = 0;

	elemdb = fopen(db_path, "r");
	/* abort on failure to open */
	if (!elemdb){
		print_err(EDBOPEN, db_path);
		/* direct return to avoid call to fclose */
		return EDBOPEN;
	}

	/* get the data for all elements */
	for (; i < evec->size; i++){
		err = get_single_data(&evec->elms[i], elemdb);
		
		/* abort if an error was returned */
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
	char new_dir[MAX_PATH_LEN] = {0};

	/* walk backwards through the path untill a seperator is found */
	while (len && path[len] != '/' && path[len] != '\\'){
		len--;
	}
	if (len == 0)
		/* no seperator found, so assume current dir */
		strcpy(new_dir, "./");
	else if (len + DB_NAME_LEN + 2 < MAX_PATH_LEN)
		/* copy the first 'len + 1' chars of len which is the actual path */
		strncpy(new_dir, path, len + 1);
	else 
		/* return error if the path is too large */
		return len;

	sprintf(db_path, "%s%s", new_dir, db_name);

	return 0;
}

static int get_single_data(struct pe_elem *elm, FILE *elemdb)
{
	int err = 0;
	char tmp[64] = {0};

	err = walk_to_elem(elm->sname, elemdb);
	if (err)
		return err;

	err = confirm_seperator(elemdb);
	if (err)
		return err;

	/* read the weigth of the element */
	fscanf(elemdb, "%[^;]", tmp);
	elm->weight = str_to_double(tmp);

	err = confirm_seperator(elemdb);
	if (err)
		return err;

	/* read the full name of the element */
	fscanf(elemdb, "%[^;]", elm->lname);

	return 0;
}

static int walk_to_elem(char name[4], FILE *elemdb)
{
	char raw[4] = {0, 0, 0, 0};
	int did_rewind = 0;
	char* resp;

	resp = fgets(raw, 4, elemdb);
	/* walk untill the names match */
	while (strncmp(name, raw, 3)){
		to_next_line(elemdb, 0);
		if (!resp){
			if (!did_rewind){
				/* first time we reach EOF, so we might not have */
				/* read the whole file */
				rewind(elemdb);
				did_rewind = 1;
			} else { 
				/* this is the second time we have walked the file*/
				/* so abort and print error message. */
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
	/* walk to next line or end of file */
	do {
		crnt = fgetc(f);
	} while (crnt != '\n' && crnt != EOF);
	
	/* walk to offset */
	if (crnt != EOF){
		while (offset--){
			fgetc(f);
		}
	}
}

static double str_to_double(char* str)
{
	double digits = 0.0;
	double divide = 1.0f;
	int met_dot = 0;

	while (*str){
		if (met_dot){
			divide *= 10.0;
		}
		if (isdigit(*str)){
			/* met a digit */
			digits *= 10.0;
			digits += ((*str) - '0');
		} else if ((*str) == '.' || (*str) == ','){
			/* met a dot or comma */
			met_dot = 1;
		}
		str++;
	}

	return digits / divide;
}

static int confirm_seperator(FILE* f)
{
	if (fgetc(f) != ';'){
		print_err(EDBFMT, "missing a seperating semicolon");
		return EDBFMT;
	}
	return 0;
}