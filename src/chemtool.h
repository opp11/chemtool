#ifndef __CHEMTOOL_H__
#define __CHEMTOOL_H__

#include "db_read.h"
#include "err_handling.h"
#include "input_parse.h"

void run_chemtool(int arg_count, char** arg_vec);
void sort_elems(int elm_count, struct pe_elem *elms);

#endif /* __CHEMTOOL_H__ */
