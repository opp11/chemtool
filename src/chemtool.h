#ifndef __CHEMTOOL_H__
#define __CHEMTOOL_H__

#include <stdio.h>
#include <string.h>
#include "elem_vec.h"
#include "db_read.h"
#include "err_handling.h"
#include "input_parse.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 *Runs the chemtool program on the input string 'in' and stores the retrieved
 *data in the provided elem_vec. The elem_vec must have beem allocated by a
 *previous call to create_elem_vec. On any error it immediately aborts, 
 *prints an error message with print_err and returns the error code.
 *
 *params:
 *	in   - The input string containing a chemical formula.
 *	evec - The elem_vec where the data will be stored
 *
 *returns:
 *	int - 0 on success.
 *	      EDBOPEN if the database file could not be found.
 *	      EFORMAT if the database file is not formatted right / corrupted.
 *	      EENAME if an element could not be found.
 *	      EARGFMT if the formula is formatted wrong.
 *	      EOOMEM on memory failure.
 */
int process_input(const char *in, struct elem_vec *evec);

#ifdef __cplusplus
}
#endif

#endif /* __CHEMTOOL_H__ */
