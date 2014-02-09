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
 *found then 'elms' and 'size' are modified. On success returns the new 
 *elem_vec and on failure returns NULL, at which point the elem_vec should be
 *considered ruined and therefore destroyed by a call to 'destroy_elm_vec'.
 *
 *params:
 *	evec - The elem_vec to shorten. Will be modified.
 *
 *returns:
 *	struct elem_vec* - pointer to the new shortened elem_vec on success.
 *	                   NULL on failure.
 */
struct elem_vec *shorten_elm_vec(struct elem_vec *evec);

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

int run_chemtool(char *in);

#endif /* __CHEMTOOL_H__ */
