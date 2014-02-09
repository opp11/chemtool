#include "chemtool.h"

int main(int argc, char** argv)
{
	char in[BUFSIZ];
	if (argc == 1){
		printf("Please write a chemical formula:\n");
		fgets(in, BUFSIZ, stdin);
		//remove trailing newline char
		size_t last = strnlen(in, BUFSIZ) - 1;
		if (in[last] == '\n')
			in[last] = '\0';			
		printf("--------------------------------------------------\n");
		return run_chemtool(in);
	} else {
		return run_chemtool(argv[1]);
	}
}
