#include "db_read.h"

int main(int argc, char** argv)
{
	struct pe_elem elm;

	if (argc > 1){
		elm.name[0] = argv[1][0];
		elm.name[1] = argv[1][1] ? argv[1][1] : ' ';
		elm.name[2] = argv[1][2] && argv[1][1] ? argv[1][2] : ' '; 

		switch(get_elem_weights(1, &elm)){
		case EFOPEN:
			printf("Could not open elem database\n");
			break;
		case EENAME:
			printf("Could not find elem\n");
			break;
		case EFORMAT:
			printf("Database not formatted correctly\n");
			break;
		default://on success
			printf("%f\n", elm.weight);
		}
	}

	return 0;
}
