#ifndef __INPARSE_H__
#define __INPARSE_H__

#include <stdlib.h>
#include <ctype.h>
#include "err_handling.h"
#include "elem_vec.h"

#ifdef __cplusplus
extern "C" {
#endif

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
int parse_input(const char *in, struct elem_vec *evec);

#ifdef __cplusplus
}
#endif

#endif /* __INPARSE_H__ */
