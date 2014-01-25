#include "chemtool.h"

int main(void)
{
	struct pe_elem elms[3];
	elms[0].name[0] = 'E';
	elms[0].name[1] = 'u';
	elms[0].name[2] = ' ';
	elms[1].name[0] = 'F';
	elms[1].name[1] = 'e';
	elms[1].name[2] = ' ';
	elms[2].name[0] = 'U';
	elms[2].name[1] = 'u';
	elms[2].name[2] = 'b';

	switch(get_elem_weights(3, elms)){
	case EFOPEN:
		printf("Could not open elem database\n");
		break;
	case EENAME:
		printf("Could not find elem\n");
		break;
	case EFORMAT:
		printf("Database not formatted correctly\n");
		break;
	default://on success
		printf("%f\n", elms[0].weight);
		printf("%f\n", elms[1].weight);
		printf("%f\n", elms[2].weight);
	}

	return 0;
}
