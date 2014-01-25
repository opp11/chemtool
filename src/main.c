#include "chemtool.h"

int main(void)
{
	FILE *f = NULL;
	char raw[3] = {'E', 'u', ' '};
	char w[13];
	f = fopen("./elemdb.csv", "r");

	walk_to_elem(raw, f);
	fgetc(f);
	fgets(w, 13, f);
	printf("%s\n", w);	

	fclose(f);
	return 0;
}
