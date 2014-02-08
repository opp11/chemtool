#include "chemtool.h"

int run_chemtool(char* in, int flags)
{
	int elm_count;
	struct pe_elem *elms;
	int err = 0;
	int i = 0;
	double tot_weight = 0.0;

	elm_count = get_num_elems(in);
	elms = create_elm_vec(elm_count);

	err = parse_input(in, elm_count, elms);
	if (err)
		goto exit;
	err = get_elem_weights(elm_count, elms);
	if (err)
		goto exit;

	for (i = 0; i < elm_count; i++){
		tot_weight += elms[i].weight * elms[i].quantity;
		printf("%s\t%i\t%f\n", elms[i].name, elms[i].quantity, 
			elms[i].weight);
	}
	printf("----------------------------------------\n");
	printf("Total Molar mass: %f\n", tot_weight);

exit:
	print_err(err);
	destroy_elm_vec(elms);
	return err;
}
