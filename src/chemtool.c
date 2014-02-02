#include "chemtool.h"

//Sorts the array of elements based on their names, so they are in 
//alpabetical order. Uses bubble sort.
static void sort_elems(int elm_count, struct pe_elem *elms);

//Returns true if lhs <= rhs
static int compare_names(char lhs[3], char rhs[3]);

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
	sort_elems(elm_count, elms);
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

void sort_elems(int elm_count, struct pe_elem *elms)
{
	int i;
	struct pe_elem tmp;
	int sorting;
	int crnt_end = elm_count - 1;

	do {
		sorting = 0;
		for (i = 0; i < crnt_end; i++){
			if (!compare_names(elms[i].name, elms[i + 1].name)){
				sorting = 1;
				tmp = elms[i];
				elms[i] = elms[i + 1];
				elms[i + 1] = tmp;
			}
		}
		crnt_end--;
	} while (sorting);
}

static int compare_names(char lhs[3], char rhs[3])
{
	int i;
	for (i = 0; i < 3; i++){
		if (lhs[i] < rhs[i])
			return 1;
		else if (lhs[i] > rhs[i])
			return 0;
	}
	return 1;
}
