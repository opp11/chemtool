#include "chemtool.h"

int main(void)
{
	FILE *f = NULL;
	f = fopen("./elemdb.csv", "r");
	printf("%c", fgetc(f));
	printf("%c\n", fgetc(f));
	to_next_line(f);
	printf("%c", fgetc(f));
	printf("%c\n", fgetc(f));
	fclose(f);
	return 0;
}
