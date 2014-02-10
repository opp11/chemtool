#include <Python.h>
#include "chemtool.h"

#define PYFUNC(fname) PyObject *fname(PyObject *self, PyObject *args)

static void copy_to_pylist(struct elem_vec *evec, PyObject *lst);

static PYFUNC(py_process_input)
{
	PyObject *out_lst = NULL;
	const char *in = NULL;
	struct elem_vec *evec = NULL;

	if (!PyArg_ParseTuple(args, "s", &in))
		goto exit;

	evec = create_elem_vec(in);
	if (!evec)
		goto exit;

	if (process_input(in, evec))
		goto exit;
	
	out_lst = PyList_New(evec->size);
	if (!out_lst)
		goto exit;

	copy_to_pylist(evec, out_lst);
exit:
	destroy_elem_vec(evec);
	return out_lst;
}

static void copy_to_pylist(struct elem_vec *evec, PyObject *lst)
{
	int i;
	for (i = 0; i < evec->size; i++){
		PyList_SET_ITEM(lst, i, Py_BuildValue("ssid",
			evec->elms[i].sname, evec->elms[i].lname, 
			evec->elms[i].quant, evec->elms[i].weight));
	}
}

PyMethodDef mod_methods[] = {
	{"process_input", py_process_input, METH_VARARGS},
	{NULL, NULL}
};

void initchemtool()
{
	Py_InitModule("chemtool", mod_methods);
}
