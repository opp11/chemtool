#ifndef __ERRHAN_H__
#define __ERRHAN_H__

#include <stdio.h>

#define EFOPEN  1 //Could not open file
#define EENAME  2 //Could not find element
#define EDBFMT  3 //Data is formatted wrong
#define EARGFMT 4 //Argument is formatted wrong

void print_err(int err);

#endif /* __ERRHAN_H__ */
