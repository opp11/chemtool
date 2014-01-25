#include "chemtool.h"

int main(void)
{
	FILE *f = NULL;
	char raw[3] = {'d', 'u', ' '};
	char w[13];
	f = fopen("./elemdb.csv", "r");

	if (walk_to_elem(raw, f)){
		printf("Reached end of file before match\n");
	} else {
		fgetc(f);
		fgets(w, 13, f);
		printf("%s\n", w);
	}	

	fclose(f);
	return 0;
}
