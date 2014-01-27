#ifndef __INPARSE_H__
#define __INPARSE_H__

#include <stdlib.h>
#include "db_read.h"
#include "err_handling.h"

int parse_input(char *in, int num_elms, struct pe_elem *elms);

struct pe_elem *create_elm_vec(char *in);
void destroy_elm_vec(struct pe_elem *vec);

#endif /* __INPARSE_H__ */
