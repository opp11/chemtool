#include "input_parse.h"

static int handle_num(int *pos, char *in, struct pe_elem *crnt_elm);
static int handle_elem(int *pos, char *in, struct pe_elem *crnt_elm);
static int handle_start_paren(int *pos, char *in);
static int handle_end_paren(int *pos, char *in, struct pe_elem *crnt_elm);
static void apply_paren_mult(int mult, int elm_count, struct pe_elem *crnt_elm);
static void prepare_elms(struct elem_vec *evec);
static int parens_faulty(char *in);

int parse_input(char *in, struct elem_vec *evec)
{
	int err = 0;
	int in_i = 0;
	int elm_i = 0;
	int first_elem = 1;

	if (parens_faulty(in))
		return EARGFMT;

	prepare_elms(evec);
	while (in[in_i]){
		if (isalpha(in[in_i])){
			if (first_elem)
				first_elem = 0;
			else
				elm_i++;
			err = handle_elem(&in_i, in, &evec->elms[elm_i]);
		} else if (isdigit(in[in_i])){
			err = handle_num(&in_i, in, &evec->elms[elm_i]);
		} else if (in[in_i] == ')'){
			err = handle_end_paren(&in_i, in, &evec->elms[elm_i]);
		} else if (in[in_i] == '('){
			err = handle_start_paren(&in_i, in);
		} else {
			err = EARGFMT;
		}
		if (err)
			//In case of any errors, abort and send error back
			return err;
	}

	return 0;
}

static int handle_num(int *pos, char *in, struct pe_elem *crnt_elm)
{
	int i = 0;
	char buffer[BUFSIZ] = {'\0'};

	if (*pos == 0)
		//A chemical formula cannot start with a number (for now...),
		//so abort and return argument format error
		return EARGFMT;

	while (isdigit(in[*pos])){
		buffer[i] = in[*pos];
		i++;
		(*pos)++;
	}

	crnt_elm->quant = strtol(buffer, NULL, 10);

	return 0;
}

static int handle_elem(int *pos, char *in, struct pe_elem *crnt_elm)
{
	int i = 0;

	//First check if the first letter of the elem is uppercase
	//and if not abort and return element error
	if (isupper(in[*pos])){
		crnt_elm->sname[i] = in[*pos];
		i++;
		(*pos)++;
	} else {
		return EENAME;
	}

	while (islower(in[*pos])){
		if (i > 2)
			//An element name cannot be longer than 3 letters,
			//so if that happens abort and return element error.
			return EENAME;
		crnt_elm->sname[i] = in[*pos];
		i++;
		(*pos)++;
	}

	return 0;
}

static int handle_start_paren(int *pos, char *in)
{
	(*pos)++;
	return isupper(in[*pos]) ? 0 : EARGFMT;
}

static int handle_end_paren(int *pos, char *in, struct pe_elem *crnt_elm)
{
	int i = *pos;
	int mult = 1;
	int paren_lvl = 0;
	int elm_count = 0;

	(*pos)++;
	//get the value of the multiplier for this paren now,
	//so we can apply it later
	if (isdigit(in[*pos])){
		struct pe_elem tmp;
		handle_num(pos, in, &tmp);
		mult = tmp.quant;
	}		

	//walk backwards through the input string untill that matching
	//start paren is found.
	i--;
	while (in[i] != '(' || paren_lvl > 0){
		//make sure nested parens are handled correct, by counting
		//what 'nesting level' we are at.
		if (in[i] == ')')
			paren_lvl++;
		else if (in[i] == '(')
			paren_lvl--;
		//Count how many element will be affected by the paren
		else if (isupper(in[i]))
			elm_count++;
		i--;
	}

	apply_paren_mult(mult, elm_count, crnt_elm);

	return 0;
}

static void apply_paren_mult(int mult, int elm_count, struct pe_elem *crnt_elm)
{
	if (mult == 1)
		return;
	while (elm_count){
		crnt_elm->quant *= mult;
		--elm_count;
		--crnt_elm;
	}
}

static void prepare_elms(struct elem_vec *evec)
{
	int i;
	for (i = 0; i < evec->size; i++){
		evec->elms[i].sname[0] = ' ';
		evec->elms[i].sname[1] = ' ';
		evec->elms[i].sname[2] = ' ';
		evec->elms[i].sname[3] = '\0';
		evec->elms[i].quant = 1;
	}
}

static int parens_faulty(char *in)
{
	int paren_lvl = 0;
	while (*in){
		if ((*in) == '(')
			paren_lvl++;
		else if ((*in) == ')')
			paren_lvl--;

		in++;
	}
	return paren_lvl;
}
