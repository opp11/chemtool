#ifndef __CHEMTOOL_H__
#define __CHEMTOOL_H__

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

int get_data(struct pe_elem *elm, FILE *elemdb);

int walk_to_elem(char name[3], FILE *elemdb);

void extract_data(struct pe_elem *elm, FILE *elemdb);

void to_next_line(FILE *f, int offset);

#endif /* __CHEMTOOL_H__ */
