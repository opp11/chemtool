#include "chemtool.h"

int main(void)
{
	FILE *elemdb = fopen("./elemdb.csv", "r");
	fclose(elemdb);
	return 0;
}
