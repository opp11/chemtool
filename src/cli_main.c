#include "chemtool.h"

//Prints the content of the provided elem_vec to the console nicely formatted.
void print_elems(struct elem_vec *evec);

int main(int argc, char** argv)
{
	char in[BUFSIZ];
	struct elem_vec *evec;

	set_db_path(argv[0]);

	if (argc == 1){
		//no element was provided at startup, so we ask for one
		printf("Please write a chemical formula:\n");
		fgets(in, BUFSIZ, stdin);
		size_t last = strlen(in) - 1;
		//abort without doing anything if the input is empty
		if (last == 0)
			return 0;

		//remove trailing newline char
		if (in[last] == '\n')
			in[last] = '\0';

		printf("--------------------------------------------------\n");
	} else {
		strncpy(in, argv[1], BUFSIZ);
	}

	evec = create_elem_vec(in);
	if (!evec){
		//cannot allocate
		print_err(EOOMEM, "not enough unused RAM.");
		return 0;
	}
	if (!process_input(in, evec))
		//no errors returned
		print_elems(evec);

	printf("Press enter to exit. ");
	//wait for enter
	fgetc(stdin);
	destroy_elem_vec(evec);
	return 0;
}

void print_elems(struct elem_vec *evec)
{
	int i;
	double tot_weight = 0.0;
	for (i = 0; i < evec->size; i++){
		tot_weight += evec->elms[i].weight * evec->elms[i].quant;
		printf("%s%6i\t%10f g/mol\t%s\n", evec->elms[i].sname, 
			evec->elms[i].quant,	evec->elms[i].weight, 
			evec->elms[i].lname);
	}
	printf("--------------------------------------------------\n");
	printf("Total Molar mass: %f g/mol\n\n", tot_weight);
}