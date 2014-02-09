#include "chemtool.h"

int main(int argc, char** argv)
{
	if (argc > 1)
		return run_chemtool(argv[1]);
	else
		return 0;
}
