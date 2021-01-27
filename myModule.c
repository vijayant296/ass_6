#include <Python.h>
int Cfactorial(int n)
{
  if (n == 0)
  	return 1;
  else
  	return n * Cfactorial(n-1);
 }


static PyObject* factorial(PyObject* self, PyObject* args)
{
	int n;
	if (!PyArg_ParseTuple(args,"i",&n))
		return NULL;
	return Py_BuildValue("i",Cfactorial(n));
}


static PyObject* version(PyObject* self)
{
	return Py_BuildValue("s","Version 1.0");
}


static PyMethodDef myMethods[] = {
	{"factorial", factorial, METH_VARARGS, "Calculates the factorial of a number."},
	{"version", (PyCFunction)version, METH_NOARGS, "returns the version"},
	{NULL,NULL,0,NULL}
};

static struct PyModuleDef myModule = {

	PyModuleDef_HEAD_INIT,
	"myModule",
	"Factorial Module",
	-1,
	myMethods
};

PyMODINIT_FUNC PyInit_myModule(void)
{
	return PyModule_Create(&myModule);
}

