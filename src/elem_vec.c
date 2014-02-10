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

	//First try to allocate all the pe_elems, and if that fails abort
	evec = calloc(ecount, sizeof(struct pe_elem));
	if (!evec)
		return NULL;

	//Then try to allocate the elem_vec. If that fails then deallocate the
	//pe_elems and abort.
	out = malloc(sizeof(struct elem_vec));
	if (out){
		out->size = ecount;
		out->elms = evec;
	} else {
		free(evec);
	}
	return out;
}

int shorten_elem_vec(struct elem_vec *vec)
{
	int crnt_e = 0;
	int new_size = vec->size;
	struct pe_elem *new_elms;

	while (crnt_e < vec->size){
		new_size -= group_dublicates(crnt_e, vec);
		crnt_e++;
	}
	if (new_size == vec->size)
		//no elems were grouped so no need to shorten
		return 0;

	new_elms = calloc(new_size, sizeof(struct pe_elem));
	if (!new_elms){
		print_err(EOOMEM, "not enough unused RAM.");
		return EOOMEM;
	}
	
	transfer_elems(new_elms, vec);
	free(vec->elms);
	vec->elms = new_elms;
	vec->size = new_size;

	return 0;
}

void destroy_elem_vec(struct elem_vec *vec)
{
	free(vec->elms);
	free(vec);
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
	int out = 0;
	//abort if this element has been zeroed out
	if (!vec->elms[crnt_e].quant)
		return 0;
	i++;
	while (i < vec->size){
		if (vec->elms[i].quant && !strncmp(vec->elms[crnt_e].sname,
				vec->elms[i].sname, 3)){
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
