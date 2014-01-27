#ifndef __DBREAD_H__
#define __DBREAD_H__

#include <stdio.h>
#include <stdlib.h>

#define EFOPEN 1
#define EENAME 2
#define EFORMAT 3

struct pe_elem {
	char name[3];
	int quantity;
	double weight;
};

int get_elem_weights(int elm_count, struct pe_elem *elm_vec);

#endif /* __DBREAD_H__ */
