#include "chemtool.h"

int main(int argc, char** argv)
{
	char in[BUFSIZ];
	struct elem_vec *evec;

	if (argc == 1){
		printf("Please write a chemical formula:\n");
		fgets(in, BUFSIZ, stdin);
		size_t last = strnlen(in, BUFSIZ) - 1;
		//abort without doing anything if the input is empty
		if (last == 0)
			return 0;

		//remove trailing newline char
		if (in[last] == '\n')
			in[last] = '\0';

		printf("--------------------------------------------------\n");
	} else {
		strncpy(in, argv[1], BUFSIZ);
	}

	evec = create_elem_vec(in);
	if (!evec){
		//cannot allocate
		print_err(EOOMEM, "not enough unused RAM.");
		return 0;
	}
	if (!process_input(in, evec))
		//no errors returned
		print_elems(evec);
	destroy_elem_vec(evec);
	return 0;
}
