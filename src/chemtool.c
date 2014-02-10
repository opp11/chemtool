#include "chemtool.h"

int process_input(const char* in, struct elem_vec *evec)
{
	int err = 0;

	err = parse_input(in, evec);
	if (err)
		goto exit;
	err = shorten_elem_vec(evec);
	if (err)
		goto exit;
	err = get_elem_data(evec);
	if (err)
		goto exit;

exit:
	return err;
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
