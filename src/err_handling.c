#include "err_handling.h"

void print_err(int err, const char* msg)
{
	switch(err){
	case EFOPEN:
		fprintf(stderr, "Could not open the element database. Expected at: %s\n", msg);
		break;
	case EENAME:
		fprintf(stderr, "Could not find element: %s\n", msg);
		break;
	case EDBFMT:
		fprintf(stderr, "Database not as expected: %s\n", msg);
		break;
	case EARGFMT:
		fprintf(stderr, "Input not formatted correctly: %s\n", msg);
		break;
	case EOOMEM:
		fprintf(stderr, "Ran out of RAM while running the program: %s\n", msg);
		break;
	}
}
