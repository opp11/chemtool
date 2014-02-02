#include "chemtool.h"

//Sorts the array of elements based on their names, so they are in 
//alpabetical order. Uses bubble sort.
//static void sort_elems(int elm_count, struct pe_elem *elms);

//Returns true if lhs <= rhs
static int compare_names(char lhs[3], char rhs[3]);

void run_chemtool(int arg_count, char** arg_vec)
{
	int elm_count;
	struct pe_elem *elms;
	int err = 0;
	int i = 0;
	double tot_weight = 0.0;

	elm_count = get_num_elems(arg_vec[1]);
	elms = create_elm_vec(elm_count);

	err = parse_input(arg_vec[1], elm_count, elms);
	if (err)
		goto exit;
	sort_elems(elm_count, elms);
	err = get_elem_weights(elm_count, elms);
	if (err)
		goto exit;

	for (i = 0; i < elm_count; i++){
		tot_weight += elms[i].weight;
	}
	printf("M = %f\n", tot_weight);

exit:
	print_err(err);
	destroy_elm_vec(elms);
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
