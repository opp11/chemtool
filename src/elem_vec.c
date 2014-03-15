#include "elem_vec.h"

//Returns the number of elements in the input string. 
//May be more than required, since dublicates are not accounted for.
static int get_num_elems(const char *in);

//Marks the dublicates of crnt_e by zeroing out their 'quant' field.
//Also adds their 'quant' field to crnt_e's 'quant' field. Returns the amount
//of elems marked.
static int group_dublicates(int crnt_e, struct elem_vec *vec);

//Transfer the unique elements from 'vec' into 'new_elems'.
static void transfer_elems(struct pe_elem *new_elms, struct elem_vec *vec);

struct elem_vec *create_elem_vec(const char* in)
{
	struct pe_elem *evec = NULL;
	struct elem_vec *out = NULL;
	int ecount = get_num_elems(in);

	//First try to allocate all the pe_elems, and if that fails abort.
	evec = (struct pe_elem*)calloc(ecount, sizeof(struct pe_elem));
	if (!evec){
		print_err(EOOMEM, "not eough unused RAM.");
		return NULL;
	}

	//Then try to allocate the elem_vec. If that fails then deallocate the
	//pe_elems and abort.
	out = (struct elem_vec*)malloc(sizeof(struct elem_vec));
	if (out){
		out->size = ecount;
		out->elms = evec;
	} else {
		print_err(EOOMEM, "not eough unused RAM.");
		free(evec);
	}
	return out;
}

int shorten_elem_vec(struct elem_vec *evec)
{
	int crnt_e = 0;//Index of current element
	int new_size = evec->size;
	struct pe_elem *new_elms;

	//Attempt to the dublicates of all elements in the vector
	while (crnt_e < evec->size){
		new_size -= group_dublicates(crnt_e, evec);
		crnt_e++;
	}
	if (new_size == evec->size)
		//No elements were grouped so no need to shorten
		return 0;

	//Allocate new internal array of pe_elems and if that fails abort
	new_elms = (struct pe_elem*)calloc(new_size, sizeof(struct pe_elem));
	if (!new_elms){
		print_err(EOOMEM, "not enough unused RAM.");
		return EOOMEM;
	}
	
	transfer_elems(new_elms, evec);
	//Free old internal array
	free(evec->elms);

	evec->elms = new_elms;
	evec->size = new_size;

	return 0;
}

void destroy_elem_vec(struct elem_vec *vec)
{
	if (vec){
		free(vec->elms);
		free(vec);
	}
}

static int get_num_elems(const char *in)
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

static int group_dublicates(int crnt_e, struct elem_vec *vec)
{
	int i = crnt_e;
	int out = 0;//Number of elements marked

	//Abort if this element has been zeroed out
	if (!vec->elms[crnt_e].quant)
		return 0;
	i++;
	//Walk all elements after this one
	while (i < vec->size){
		if (!strncmp(vec->elms[crnt_e].sname, vec->elms[i].sname, 3)){
			//Names match so tansfer the quant field, and mark this
			//element.
			vec->elms[crnt_e].quant += vec->elms[i].quant;
			vec->elms[i].quant = 0;
			out++;
		}
		i++;
	}
	return out;
}

static void transfer_elems(struct pe_elem *new_elms, struct elem_vec *vec)
{
	int i = 0;
	while (i < vec->size){
		if (vec->elms[i].quant){
			(*new_elms) = vec->elms[i];
			new_elms++;
		}
		i++;
	}
}
