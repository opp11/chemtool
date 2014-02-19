#include "err_handling.h"

static void std_report_err(int err, const char *msg)
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
	default:
		fprintf(stderr, "An unknown error was reported. This might mean the program file is corrupted.\nConsider reinstalling the program.\n");
		break;
	}
}

static void (*report_err)(int err, const char *msg) = std_report_err;

void print_err(int err, const char* msg)
{
	(*report_err)(err, msg);
}

void set_err_reporter(void (*err_reporter)(int, const char*))
{
	report_err = err_reporter;
}
