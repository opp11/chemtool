#include "chemtool.h"

int process_input(const char* in, struct elem_vec *evec)
{
	int err = 0;

	err = parse_input(in, evec);
	if (err)
		goto exit;
	err = shorten_elem_vec(evec);
	if (err)
		goto exit;
	err = get_elem_data(evec);
	if (err)
		goto exit;

exit:
	return err;
}