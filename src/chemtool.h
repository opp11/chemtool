#ifndef __CHEMTOOL_H__
#define __CHEMTOOL_H__

#include <ctype.h>
#include "db_read.h"
#include "err_handling.h"
#include "input_parse.h"

struct pe_elem {
	char sname[4];
	char lname[14];
	int quant;
	double weight;
};

struct elem_vec {
	struct pe_elem* elms;
	int size;
};

/*
 *Allocates an elem_vec struct based on the input string.
 *The struct should be deacllocated with a call to 'destroy_elm_vec'.
 *
 *params:
 *	in - The input string to be analysed.
 *
 *returns:
 *	struct elem_vec* - pointer to the allocated memory on success.
 *	                   NULL on failure.
 */
struct elem_vec *create_elm_vec(char *in);

/*
 *Shortens the elem_vec by grouping dublicate elements. If dublicates are
 *found then 'elms' and 'size' are modified. On return of EOOMEM the elem_vec
 *should be considered ruined and therefore destroyed by a call to
 *'destroy_elm_vec'.
 *
 *params:
 *	evec - The elem_vec to shorten. Will be modified.
 *
 *returns:
 *	int - 0 on success.
 *	      EOOMEM on failure to allocate new elem_vec.
 */
int shorten_elm_vec(struct elem_vec *evec);

/*
 *Frees the memory previously allocated by a call to 'create_elm_vec'.
 *
 *params:
 *	vec - Pointer to the elem_vec struct to free.
 *
 *return:
 *	void
 */
void destroy_elm_vec(struct elem_vec *vec);

/*
 *Runs the chemtool program on the input string 'in'. On any error it 
 *immediately aborts, prints an error message and returns the error code.
 *
 *params:
 *	in - The input string containing a chemical formula.
 *
 *returns:
 *	int - 0 on success.
 *	      EFOPEN if the database file could not be found.
 *	      EFORMAT if the database file is not formatted right / corrupted.
 *	      EENAME if an element could not be found.
 *	      EARGFMT if the formula is formatted wrong.
 *	      EOOMEM on failure to allocate new elem_vec.
 */
int run_chemtool(char *in);

#endif /* __CHEMTOOL_H__ */
