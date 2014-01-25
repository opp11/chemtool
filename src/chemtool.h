#ifndef __CHEMTOOL_H__
#define __CHEMTOOL_H__

#include <stdio.h>

struct elem {
	char name[3];
	int quantity;
	float weight;
};

int get_weight(int elm_count, struct elem *elm_vec);

void to_next_line(FILE *f);

#endif /* __CHEMTOOL_H__ */
