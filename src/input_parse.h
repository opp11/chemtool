#ifndef __INPARSE_H__
#define __INPARSE_H__

#include <stdlib.h>
#include "db_read.h"
#include "err_handling.h"

/*
 *Parses the input string 'in' containing a chemical formula, and fills out
 *the array of pe_elem structs with the data. If an error is detected the
 *function aborts and returns an error code. The pe_elem structs filled out
 *before the error occured will have the correct data.
 *
 *params:
 *	in       - Null terminated string containing the chemical formula.
 *	num_elms - The number elements to fill out.
 *	elms     - Array containing the pe_elem structs to fill out with data.
 *
 *returns:
 *	int - 0 on success.
 *	      EENAME if an element will not exist in the database.
 *	      EARGFMT if the formula is formatted wrong.
 */
int parse_input(char *in, int num_elms, struct pe_elem *elms);

/*
 *Gets the number of elements in the chemical formula contained in 'in'.
 *
 *params:
 *	in - Null terminated string containing the chemical formula.
 *
 *returns:
 *	int - The number of elements in 'in'.
 */
int get_num_elems(char* in);

/*
 *Allocates an array of pe_elem structs containing 'elm_count' entries.
 *Must be followed by a call to 'destroy_elm_vec' to free the memory.
 *
 *params:
 *	elm_count - The number of elements to allocate memory for.
 *
 *returns:
 *	struct pe_elem* - pointer to the allocated memory on success.
 *	                  NULL on failure.
 */
struct pe_elem *create_elm_vec(int elm_count);

/*
 *Frees the memory previously allocated by a call to 'create_elm_vec'.
 *
 *params:
 *	vec - Pointer to the beginning of the array of pe_elem structs.
 *
 *return:
 *	void
 */
void destroy_elm_vec(struct pe_elem *vec);

#endif /* __INPARSE_H__ */
