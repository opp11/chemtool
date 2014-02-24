#include <Python.h>
#include "chemtool.h"
#include "err_handling.h"

#define PYFUNC(fname) PyObject *fname(PyObject *self, PyObject *args)

//Copy all elements in the elem_vec to the Python list.
static void copy_to_pylist(struct elem_vec *evec, PyObject *lst);

//Python wrapper for the chemtool function that extracts the data from the
//input string and returns a list of tuples with (sname, lname, quant, weight).
static PYFUNC(py_get_elem_data);

//Python wrapper for 'get_base_err_msg' in err_handling.h
static PYFUNC(py_get_base_err_msg);

static PYFUNC(py_get_elem_data)
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

static PYFUNC(py_get_base_err_msg)
{
	int err = 0;

	if (!PyArg_ParseTuple(args, "i", &err))
		return NULL;

	return PyString_FromString(get_base_err_msg(err));
}

//Propagate any erros reported by the chemtool functions as Python exceptions
static void py_report_err(int err, const char* msg)
{
	switch (err){
	case EFOPEN:
		PyErr_Format(PyExc_IOError, "%s%s", 
			get_base_err_msg(err), msg);
		break;
	case EOOMEM:
		PyErr_NoMemory();
		break;
	case EENAME:
		PyErr_Format(PyExc_NameError, "%s%s", 
			get_base_err_msg(err), msg);
		break;
	case EARGFMT:
		PyErr_Format(PyExc_NameError, "%s%s", 
			get_base_err_msg(err), msg);
		break;
	case EDBFMT:
		PyErr_Format(PyExc_IOError, "%s%s", 
			get_base_err_msg(err), msg);
		break;
	default:
		PyErr_Format(PyExc_RuntimeError, "%s%s", 
			get_base_err_msg(err), msg);
		break;
	}
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
	{"get_elem_data", py_get_elem_data, METH_VARARGS},
	{"get_base_err_msg", py_get_base_err_msg, METH_VARARGS},
	{NULL, NULL}
};

void initchemtool()
{
	//handle to the module
	PyObject *mod;

	//the error values as Python objects
	PyObject *py_efopen = PyLong_FromLong(EFOPEN);
	PyObject *py_eename = PyLong_FromLong(EENAME);
	PyObject *py_edbfmt = PyLong_FromLong(EDBFMT);
	PyObject *py_eargfmt = PyLong_FromLong(EARGFMT);
	PyObject *py_eoomem = PyLong_FromLong(EOOMEM);

	set_err_reporter(py_report_err);
	mod = Py_InitModule("chemtool", mod_methods);

	//make the error values visible for Python in our module's scope
	PyObject_SetAttrString(mod, "err_file_open", py_efopen);
	Py_DECREF(py_efopen);
	PyObject_SetAttrString(mod, "err_elm_name", py_eename);
	Py_DECREF(py_eename);
	PyObject_SetAttrString(mod, "err_db_format", py_edbfmt);
	Py_DECREF(py_edbfmt);
	PyObject_SetAttrString(mod, "err_arg_format", py_eargfmt);
	Py_DECREF(py_eargfmt);
	PyObject_SetAttrString(mod, "err_no_memory", py_eoomem);
	Py_DECREF(py_eoomem);
}
