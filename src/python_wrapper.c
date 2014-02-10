#include <Python.h>
#include "chemtool.h"

#define PYFUNC(fname) PyObject *fname(PyObject *self, PyObject *args)

PYFUNC(py_process_input)
{
	PyObject out_lst;
	const char *in;
}
