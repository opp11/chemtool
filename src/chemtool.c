#include "chemtool.h"

//Sorts the array of elements based on their names, so they are in 
//alpabetical order. Uses bubble sort.
static void sort_elems(int elm_count, struct pe_elem *elms);

//Returns true if lhs <= rhs
static int compare_names(char lhs[3], char rhs[3]);

void run_chemtool(int arg_count, char** arg_vec)
{
	int elm_count;
	struct pe_elem *elms;
	int err = 0;

	
}

static void sort_elems(int elm_count, struct pe_elem *elms)
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
