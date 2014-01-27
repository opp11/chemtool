#include "db_read.h"
#include "err_handling.h"

int main(int argc, char** argv)
{
	struct pe_elem elm;
	int err;

	if (argc > 1){
		elm.name[0] = argv[1][0];
		elm.name[1] = argv[1][1] ? argv[1][1] : ' ';
		elm.name[2] = argv[1][2] && argv[1][1] ? argv[1][2] : ' '; 

		err = get_elem_weights(1, &elm);
		if (!err)
			printf("%f\n", elm.weight);
		else
			print_err(err);
	}

	return 0;
}
