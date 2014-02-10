#ifndef __ERRHAN_H__
#define __ERRHAN_H__

#include <stdio.h>
#include <stdarg.h>

enum ERRCODE {
	EFOPEN = 1, //Could not open file
	EENAME, //Could not find element
	EDBFMT, //Data is formatted wrong
	EARGFMT, //Argument is formatted wrong
	EOOMEM, //Out of memory
};

/*
 *Prints an error message for the provided error code to stderr. 
 *The provided msg is also appended after the standard error message 
 *to give more context.
 *
 *params:
 *	err - Error code to print a message for.
 *	msg - Message giving context to the error type.
 *
 *returns:
 *	void
 */
void print_err(int err, const char* msg);

#endif /* __ERRHAN_H__ */
