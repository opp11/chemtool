#ifndef __CHEMTOOL_H__
#define __CHEMTOOL_H__

#include <stdio.h>

struct pe_elem {
	char name[3];
	int quantity;
	float weight;
};

int get_elem_weights(int elm_count, struct pe_elem *elm_vec);

int get_weight(struct pe_elem *elm, FILE *elemdb);

int walk_to_elem(char name[3], FILE *elemdb);

void to_next_line(FILE *f, int offset);

#endif /* __CHEMTOOL_H__ */
