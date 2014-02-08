#include "chemtool.h"

static int get_num_elems(char *in);

struct elem_vec *create_elm_vec(char* in)
{
	struct pe_elem *evec = NULL;
	struct elem_vec *out = NULL;
	int ecount = get_num_elems(in);

	evec = calloc(ecount, sizeof(struct pe_elem));
	if (!evec)
		return NULL;

	out = malloc(sizeof(struct elem_vec));
	if (out){
		out->size = ecount;
		out->elms = evec;
	} else {
		free(evec);
	}
	return out;
}

void destroy_elm_vec(struct elem_vec *vec)
{
	free(vec->elms);
	free(vec);
}

int run_chemtool(char* in)
{
	struct elem_vec *evec;
	int err = 0;
	int i = 0;
	double tot_weight = 0.0;

	evec = create_elm_vec(in);

	err = parse_input(in, evec);
	if (err)
		goto exit;
	err = get_elem_data(evec);
	if (err)
		goto exit;

	for (i = 0; i < evec->size; i++){
		tot_weight += evec->elms[i].weight * evec->elms[i].quant;
		printf("%s\t%i\t%f\t%s\n", evec->elms[i].sname, 
			evec->elms[i].quant,	evec->elms[i].weight, 
			evec->elms[i].lname);
	}
	printf("--------------------------------------------------\n");
	printf("Total Molar mass: %f\n\n", tot_weight);

exit:
	print_err(err);
	destroy_elm_vec(evec);
	return err;
}

static int get_num_elems(char *in)
{
	int out = 0;
	//Since all elements begin with an uppercase letter we simply
	//count the number of uppercase letters in the input to get how
	//many elements were entered.
	while (*in){
		if (isupper(*in))
			out++;

		in++;
	}

	return out;
}
