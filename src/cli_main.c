#include <stdio.h>
#include "chemtool.h"

#define BUFFERSIZE 8192

/* Prints the content of the provided elem_vec to the console. */
void print_elems(struct elem_vec *evec);

int main(int argc, char** argv)
{
	char in[BUFFERSIZE];
	struct elem_vec *evec;

	set_db_path(argv[0]);

	if (argc == 1){
		/* No formula was provided at startup, so we ask for one */
		printf("Please write a chemical formula:\n");
		fgets(in, BUFFERSIZE, stdin);
		size_t last = strlen(in) - 1;
		/* Abort without doing anything if the input is empty */
		if (last == 0)
			return 0;

		/* Remove trailing newline char, if any */
		if (in[last] == '\n')
			in[last] = '\0';

		printf("--------------------------------------------------\n");
	} else {
		/* Formula was given, so copy it into 'in'. */
		strncpy(in, argv[1], BUFFERSIZE);
	}

	evec = create_elem_vec(in);
	if (!evec){
		/* Could not allocate, so abort. */
		return 0;
	}
	if (!process_input(in, evec)){
		/* No errors returned, so print the element vector */
		print_elems(evec);
	}

	/* If no commandline arguments were given we pause */
	/* to give the user time to read the output. */
	if (argc == 1){
		printf("Press enter to exit. ");
		/* Wait for enter */
		fgetc(stdin);
	}
	destroy_elem_vec(evec);
	return 0;
}

void print_elems(struct elem_vec *evec)
{
	int i;
	double tot_weight = 0.0;
	for (i = 0; i < evec->size; i++){
		tot_weight += evec->elms[i].weight * evec->elms[i].quant;
		/* print the data to screen in the following order: */
		/* <short name> \t <quantity> \t <molar mass> \t <long name> */
		printf("%s%6i\t%10f g/mol\t%s\n", 
			evec->elms[i].sname, 
			evec->elms[i].quant,	
			evec->elms[i].weight, 
			evec->elms[i].lname);
	}
	printf("--------------------------------------------------\n");
	printf("Total Molar mass: %f g/mol\n\n", tot_weight);
}