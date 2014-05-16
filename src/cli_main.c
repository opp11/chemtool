#include <stdio.h>
#include <unistd.h>
#include "chemtool.h"

#define BUFFERSIZE 8192

enum CHEMTOOL_OPTS {
	OPT_SPARSE  = 's',/* Only print total molar mass */
	OPT_QUIET   = 'q' /* Only print parse results */
};
static const char *OPTS_STRING = "sq";

/* Option flags */
int sparse_mode = 0;
int quiet_mode = 0;

/* Parses all cli options. Returns 0 on success and 1 on failure. */
static int parse_opts(int argc, char **argv);

/* Runs chemtool on a chemical formula. */
/* Returns 0 on succes and nonzero on failure. */
static void run_tool(char *in);

/* Prints the content of the provided elem_vec to the console. */
static void print_elems(struct elem_vec *evec);

int main(int argc, char** argv)
{
	char in[BUFFERSIZE];

	set_db_path(argv[0]);

	if (parse_opts(argc, argv) == -1){
		/* Abort on failure to parse args */
		return 0;
	}
	if (optind == argc){
		/* No formula was provided at startup, so we ask for one */
		if (!quiet_mode){
			printf("Please write a chemical formula:\n");
		}
		fgets(in, BUFFERSIZE, stdin);
		size_t last = strlen(in) - 1;
		/* Abort without doing anything if the input is empty */
		if (last == 0)
			return 0;

		/* Remove trailing newline char, if any */
		if (in[last] == '\n')
			in[last] = '\0';

		if (!sparse_mode){
			printf("--------------------------------------------------\n");
		}
		run_tool(in);

		/* Wait for enter to give the user time to read the input */
		if (!quiet_mode){
			printf("Press enter to exit. ");
			fgetc(stdin);
		}
	} else {
		/* Formula was given, so run tool on all formulas. */
		while (optind < argc){
			run_tool(argv[optind]);
			optind++;
		}
	}
	return 0;
}

static int parse_opts(int argc, char **argv)
{
	int opt;
	opterr = 0;

	while ((opt = getopt(argc, argv, OPTS_STRING)) != -1){
		switch(opt){
		case OPT_QUIET:
			quiet_mode = 1;
			break;
		case OPT_SPARSE:
			sparse_mode = 1;
			break;
		case '?':
			fprintf(stderr, "Unknown option: '%c'", optopt);
			return 1;
		}
	}
	return 0;
}

static void run_tool(char *in)
{	
	struct elem_vec *evec = create_elem_vec(in);
	if (!sparse_mode){
		printf("Result for: %s\n", in);
	}
	if (!evec){
		/* Could not allocate, so abort. */
		return;
	}
	if (!process_input(in, evec)){
		/* No errors returned, so print the element vector */
		print_elems(evec);
	}
	destroy_elem_vec(evec);
}

static void print_elems(struct elem_vec *evec)
{
	int i;
	double tot_weight = 0.0;
	for (i = 0; i < evec->size; i++){
		tot_weight += evec->elms[i].weight * evec->elms[i].quant;
		/* print the data to screen in the following order: */
		/* <short name> \t <quantity> \t <molar mass> \t <long name> */
		if (!sparse_mode){
			printf("%s%6i\t%10f g/mol\t%s\n", 
				evec->elms[i].sname, 
				evec->elms[i].quant,	
				evec->elms[i].weight, 
				evec->elms[i].lname);
		}
	}
	if (!sparse_mode){
		printf("--------------------------------------------------\n");
	}
	printf("Total Molar mass: %f g/mol\n\n", tot_weight);
}