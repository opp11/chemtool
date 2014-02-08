#ifndef __DBREAD_H__
#define __DBREAD_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "err_handling.h"

struct pe_elem {
	char sname[4];
	char lname[14];
	int quantity;
	double weight;
};

/*
 *Fills out the 'weight' field for the pe_elem structs provided. The name of
 *the element to find is read from the the pe_elem struct's 'sname' field
 *and must be filled out when the function is called.
 *If an element cannot be found within the database, the function will abort
 *the read and return. Structs filled prior to the one causing the error
 *will have the correct values in their 'weight' fields.
 *
 *params:
 *	elm_count - The number of elements to get the weights of.
 *	elm_vec   - Pointer to an array of pe_elem structs to fill out.
 *
 *returns:
 *	int - 0 on succes.
 *	      EFOPEN if the database file could not be found.
 *	      EFORMAT if the database file is not formatted right / corrupted.
 *	      EENAME if an element could not be found.
 */
int get_elem_data(int elm_count, struct pe_elem *elm_vec);

#endif /* __DBREAD_H__ */
