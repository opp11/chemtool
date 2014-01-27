#ifndef __ERRHAN_H__
#define __ERRHAN_H__

#include <stdio.h>

#define EFOPEN  1
#define EENAME  2
#define EDBFMT  3
#define EARGFMT 4

void print_err(int err);

#endif /* __ERRHAN_H__ */
