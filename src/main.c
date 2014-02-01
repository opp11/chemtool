#include "db_read.h"
#include "err_handling.h"
#include "input_parse.h"

int main(int argc, char** argv)
{
	char* in = "((C2He32Uub)2H120";
	int elm_count = get_num_elems(in);
	struct pe_elem *elms = create_elm_vec(elm_count);
	int i = 0;
	int err = 0;

	err = parse_input(in, elm_count, elms);

	if (err == 0){
		while (i < elm_count){
			printf("%s %i\n", elms[i].name, elms[i].quantity);
			i++;
		}
	} else {
		print_err(err);
	}

	destroy_elm_vec(elms);
	return 0;
}
