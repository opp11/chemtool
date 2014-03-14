#include "err_handling.h"

//The standard error reporter. Simply prints the message to stderr
static void std_report_err(int err, const char *msg)
{
	fprintf(stderr, "%s%s\n", get_base_err_msg(err), msg);
}

//Function pointer to error reporter. Points to std_report_err as default.
static void (*report_err)(int err, const char *msg) = std_report_err;

void print_err(int err, const char* msg)
{
	(*report_err)(err, msg);
}

void set_err_reporter(void (*err_reporter)(int, const char*))
{
	report_err = err_reporter;
}

const char* get_base_err_msg(int err)
{	
	switch(err){
	case EDBOPEN:
		return "Could not open the element database. Expected at: ";
	case EENAME:
		return "Could not find element: ";
	case EDBFMT:
		return "Database not as expected: ";
	case EARGFMT:
		return "Input not formatted correctly: ";
	case EOOMEM:
		return "Ran out of RAM while running the program: ";
	default:
		return "An unknown error was reported. This might mean the program file is corrupted.\nConsider reinstalling the program. The error message was: ";
	}
}
