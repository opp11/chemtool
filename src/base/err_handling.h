#ifndef __ERRHAN_H__
#define __ERRHAN_H__

#include <stdio.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

enum ERRCODE {
	EDBOPEN = 1, /* Could not open file */
	EENAME,      /* Could not find element */
	EDBFMT,      /* Data is formatted wrong */
	EARGFMT,     /* Argument is formatted wrong */
	EOOMEM,      /* Out of memory */
};

/*
 *Prints an error message for the provided error code using the current
 *err_reporter. Per default this prints the error message to stderr. 
 *The provided msg is also appended after the standard error message 
 *(from get_base_err_msg) to give more context.
 *
 *params:
 *	err - Error code to print a message for.
 *	msg - Message giving context to the error type.
 *
 *returns:
 *	void
 */
void print_err(int err, const char* msg);

/*
 *Sets the function used by print_err to actually print the error. 
 *Per default this is set to a function that prints the error message to stderr.
 *
 *params:
 *	err_reporter - Function pointer to the new err_reporter. 
 *	               Returns void and takes an int and a const char*
 *returns:
 *	void
 */
void set_err_reporter(void (*err_reporter)(int, const char*));

/*
 *Gets a base error message for the provided error code. A returned error
 *message should be followed by another string giving more context to the error.
 *All returned error messages end with a colon followed by a space (": ").
 *
 *params:
 *	err - The error code to generate a message for.
 *
 *returns:
 *	const char* - A base error message ending with ": ".
 */
const char* get_base_err_msg(int err);

#ifdef __cplusplus
}
#endif

#endif /* __ERRHAN_H__ */
