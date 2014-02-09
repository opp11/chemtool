#ifndef __ERRHAN_H__
#define __ERRHAN_H__

#include <stdio.h>

#define EFOPEN  1 //Could not open file
#define EENAME  2 //Could not find element
#define EDBFMT  3 //Data is formatted wrong
#define EARGFMT 4 //Argument is formatted wrong
#define EOOMEM  5 //Out of memory

/*
 *Prints an error message for the provided error code.
 *
 *params:
 *	err - Error code to print a message for.
 *
 *returns:
 *	void
 */
void print_err(int err);

#endif /* __ERRHAN_H__ */
