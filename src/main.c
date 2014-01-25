#include "chemtool.h"

int main(void)
{
	FILE *f = NULL;
	struct pe_elem elm;
	elm.name[0] = 'x';
	elm.name[1] = 'u';
	elm.name[2] = 'f';

	f = fopen("./elemdb.csv", "r");

	if (get_weight(&elm, f))
		printf("Could not get weight\n");
	else
		printf("%f\n", elm.weight);

	fclose(f);
	return 0;
}
