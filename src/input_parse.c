#include "input_parse.h"

static inline int IS_NUM(char c)
{
	return c >= '0' && c <= '9';
}

static inline int IS_UPPER_LETTER(char c)
{
	return c >= 'A' && c <= 'Z';
}

static inline int IS_LOWER_LETTER(char c)
{
	return c >= 'a' && c <= 'z';
}

static inline int IS_LETTER(char c)
{
	return IS_UPPER_LETTER(c) || IS_LOWER_LETTER(c);
}

static int handle_num(int *pos, char *in, struct pe_elem *crnt_elm);
static int handle_elem(int *pos, char *in, struct pe_elem *crnt_elm);
static int handle_start_paren(int *pos, char *in);
static int handle_end_paren(int *pos, char *in, struct pe_elem *crnt_elm);
static void apply_paren_mult(int mult, int elm_count, struct pe_elem *crnt_elm);
static void prepare_elms(int num_elms, struct pe_elem *elms);
static int parens_faulty(char *in);

int parse_input(char *in, int num_elms, struct pe_elem *elms)
{
	int err = 0;
	int in_i = 0;
	int elm_i = 0;
	int first_elem = 1;

	if (parens_faulty(in))
		return EARGFMT;

	prepare_elms(num_elms, elms);
	while (in[in_i]){
		if (IS_LETTER(in[in_i])){
			if (first_elem)
				first_elem = 0;
			else
				elm_i++;
			err = handle_elem(&in_i, in, &elms[elm_i]);
		} else if (IS_NUM(in[in_i])){
			err = handle_num(&in_i, in, &elms[elm_i]);
		} else if (in[in_i] == ')'){
			err = handle_end_paren(&in_i, in, &elms[elm_i]);
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

	while (IS_NUM(in[*pos])){
		buffer[i] = in[*pos];
		i++;
		(*pos)++;
	}

	crnt_elm->quantity = strtol(buffer, NULL, 10);

	return 0;
}

static int handle_elem(int *pos, char *in, struct pe_elem *crnt_elm)
{
	int i = 0;

	//First check if the first letter of the elem is uppercase
	//and if not abort and return element error
	if (IS_UPPER_LETTER(in[*pos])){
		crnt_elm->sname[i] = in[*pos];
		i++;
		(*pos)++;
	} else {
		return EENAME;
	}

	while (IS_LOWER_LETTER(in[*pos])){
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
	return IS_UPPER_LETTER(in[*pos]) ? 0 : EARGFMT;
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
	if (IS_NUM(in[*pos])){
		struct pe_elem tmp;
		handle_num(pos, in, &tmp);
		mult = tmp.quantity;
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
		else if (IS_UPPER_LETTER(in[i]))
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
		crnt_elm->quantity *= mult;
		--elm_count;
		--crnt_elm;
	}
}

static void prepare_elms(int num_elms, struct pe_elem *elms)
{
	int i;
	for (i = 0; i < num_elms; i++){
		elms[i].sname[0] = ' ';
		elms[i].sname[1] = ' ';
		elms[i].sname[2] = ' ';
		elms[i].sname[3] = '\0';
		elms[i].quantity = 1;
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

int get_num_elems(char *in)
{
	int out = 0;
	//Since all elements begin with an uppercase letter we simply
	//count the number of uppercase letters in the input to get how
	//many elements were entered.
	while (*in){
		if (IS_UPPER_LETTER(*in))
			out++;

		in++;
	}

	return out;
}

struct pe_elem *create_elm_vec(int elm_count)
{
	return calloc(elm_count, sizeof(struct pe_elem));
}

void destroy_elm_vec(struct pe_elem *vec)
{
	free(vec);
}
