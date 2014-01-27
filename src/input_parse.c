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

static int parse_symbol(char sym);
static void make_element(struct pe_elem *elm, char name[3], char quant[50]);
static int handle_paren(int elm_i, struct pe_elem *elms);
static int get_num_elems(char* in);

int parse_input(char *in, int num_elms, struct pe_elem *elms)
{
	int err;
	while (*in){
		err = parse_symbol(*in, elms);
		if (err)
			return err;

		in++;
	}

	return 0;
}

static int parse_symbol(char sym, struct pe_elem *elms)
{
	static int elm_i = 0;
	static int sym_i = 0;
	static int quant_i = 0;
	static char crnt_quant[50] = {'\0'};//might as well be prepared
	static char crnt_name[3] = {' '};
	
	if (IS_NUM(sym)){
		if (elm_i){
			crnt_quant[quant_i] = sym;
			quant_i++;
		} else {
			//we cannot start with a number so abort
			//and report argument error if it happens
			return EARGFMT;
		}
	} else if (IS_UPPER_LETTER(sym)){
		if (elm_i){
			make_element(&elms[elm_i], crnt_name, crnt_quant);	
			elm_i++;
		}
		sym_i = 1;
		quant_i = 0;
		crnt_name[0] = sym;
	} else if (IS_LOWER_LETTER(sym)){
		if (sym_i < 3 && sym_i > 0){
			crnt_name[sym_i] = sym;
			sym_i++;
		} else {
			//An element name has a max length of 3 and lowecase
			//letters can only appear after the first letter.
			//Therefore if we are not within those bounds we won't
			//able to find elem and so we report an element error.
			return EENAME;
		}
	} else if (sym == ')'){
		make_element(&elms[elm_i], crnt_name, crnt_quant);
		handle_paren(elm_i, elms);
	} else if (sym == '('){
		//Do not do anything. If something is not right after the
		//open paren the other checks will catch it.
	} else {
		//This symbol does not belong in a chemical formula
		//so abort and return argument error.
		return EARGFMT;
	}

	return 0;
}

static void make_element(struct pe_elem *elm, char name[3], char quant[50])
{
	int i = 0;

	elm.name = name;
	elm.quantity = strtol(quant, NULL, 10);

	//reset name and quant
	name[0] = ' ';
	name[1] = ' ';
	name[2] = ' ';

	while (i < 50)
		quant[i] = '\0';	
}

static int handle_paren(int elm_i, struct pe_elem *elms)
{
	int paren_lvl = 0;
	
}

static int get_num_elems(char *in)
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

struct pe_elem *create_elm_vec(char* in)
{
	return calloc(get_num_elems(in), sizeof(struct pe_elem);
}

void destroy_elm_vec(struct pe_elem *vec)
{
	free(vec);
}
