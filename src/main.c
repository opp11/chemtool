#include "chemtool.h"

int main(void)
{
	FILE *f = NULL;
	char el[3] = {'E','u','\0'};
	char val[10];
	f = fopen("./elemdb.csv", "r");
	
	walk_to_elem(el, f);
	fgets(val, 10, f);
	printf(val);

	fclose(f);
	return 0;
}
