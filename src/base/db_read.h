#ifndef __DBREAD_H__
#define __DBREAD_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "elem_vec.h"
#include "err_handling.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 *Fills out the data fields of the provided elem_vec struct. The name of
 *the element to find is read from the the pe_elem struct's 'sname' field
 *and must be filled out when the function is called.
 *If an element cannot be found within the database, the function will abort
 *the read and return. Structs filled prior to the one causing the error
 *will have the correct values in their fields.
 *
 *params:
 *	evec - Pointer to an elem_vec struct to fill out.
 *
 *returns:
 *	int - 0 on succes.
 *	      EDBOPEN if the database file could not be found.
 *	      EDBFMT if the database file is not formatted right / corrupted.
 *	      EENAME if an element could not be found.
 */
int get_elem_data(struct elem_vec *evec);

/*
 *Sets the path to the directory containing the database. The function strips
 *the last word from the path (or untill a slash is encountered), so the program
 *path is a valid input. If no slash is encountered it assumes the current 
 *directory. Returns 0 if succesfully set. If the path is too long the path
 *length is returned and the operation is aborted.
 *
 *param:
 *	const char* - Path to the element database.
 *
 *returns:
 *	int - 0 on succes.
 *	      Length of path if path is too long.
 */
int set_db_path(const char* path);

#ifdef __cplusplus
}
#endif

#endif /* __DBREAD_H__ */