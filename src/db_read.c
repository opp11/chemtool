#include "db_read.h"

//Fills out the data fields of a single pe_elem struct
//by reading from the 'elemdb' file
static int get_single_data(struct pe_elem *elm, FILE *elemdb);

//Walks DOWN through the file 'elemdb' untill it reaches a mathcing name or EOF
static int walk_to_elem(char name[4], FILE *elemdb);

//Walks to the next line in the file 'f' and then 'offset' chars to the right
static void to_next_line(FILE *f, int offset);

//Converts a string to a double. We make our own since the
//normal C string conversion functions round the numbers down too
//aggressively e.g. 4.002 gets rounded to 4.0.
static double str_to_double(char* str);

//Values should be seperated by a semicolon. This returns 0 if we are on a
//semicolo now and 1 if we are not. Also moves 1 char forward in the file.
static inline int conf_septor(FILE *f)
{
	return (fgetc(f) != ';');
}

int get_elem_data(struct elem_vec *evec)
{
	FILE *elemdb = NULL;
	int i = 0;
	int err = 0;

	elemdb = fopen("./elemdb.csv", "r");
	//abort on failure to open
	if (!elemdb){
		print_err(EFOPEN, "./elemdb.csv");
		return EFOPEN;
	}

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

static int get_single_data(struct pe_elem *elm, FILE *elemdb)
{
	char tmp[BUFSIZ] = {0};
	if (walk_to_elem(elm->sname, elemdb)){
		print_err(EENAME, elm->sname);
		return EENAME;
	}

	if (conf_septor(elemdb)){
		print_err(EDBFMT, "missing a seperating semicolon.");
		return EDBFMT;
	}	
	fscanf(elemdb, "%[^;]%*[;]%[^;]", tmp, elm->lname);
	elm->weight = str_to_double(tmp);

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
		resp = fgets(raw, 4, elemdb);
		if (!resp){
			if (!did_rewind){
				rewind(elemdb);
				did_rewind = 1;
			} else { 
				//if we walked through the whole file
				//then abort and return element not found
				return EENAME;
			}
		}
	}

	return 0;
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
			digits *= 10.0;
			digits += ((*str) - '0');
		} else if ((*str) == '.' || (*str) == ','){
			met_dot = 1;
		}
		str++;
	}

	return digits / divide;
}
