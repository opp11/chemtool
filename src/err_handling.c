#include "err_handling.h"

void print_err(int err)
{
	switch(err){
	case EFOPEN:
		printf("Could not open the element database.\n");
		break;
	case EENAME:
		printf("Could not find one of the elements.\n");
		break;
	case EDBFMT:
		printf("Database not formatted correctly.\n");
		break;
	case EARGFMT:
		printf("Input not formatted correctly.\n");
		break;
	case EOOMEM:
		printf("Ran out of RAM while running the program\n");
	}
}
