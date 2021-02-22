Building a Python C Extension Module

There are several ways in which you can extend the functionality of Python. One of these is to write your Python module in C or C++. This process can lead to improved performance and better access to C library functions and system calls. In this tutorial, you’ll discover how to use the Python API to write Python C extension modules.

Extending Your Python Program
One of the lesser-known yet incredibly powerful features of Python is its ability to call functions and libraries defined in compiled languages such as C or C++. This allows you to extend the capabilities of your program beyond what Python’s built-in features have to offer.

To write Python modules in C, you’ll need to use the Python API, which defines the various functions, macros, and variables that allow the Python interpreter to call your C code. All of these tools and more are collectively bundled in the Python.h header file.

PyObject
PyObject is an object structure that you use to define object types for Python. All Python objects share a small number of fields that are defined using the PyObject structure. All other object types are extensions of this type.

PyObject tells the Python interpreter to treat a pointer to an object as an object. For instance, setting the return type of the above function as PyObject defines the common fields that are required by the Python interpreter in order to recognize this as a valid Python type.

PyArg_ParseTuple()
PyArg_ParseTuple() parses the arguments you’ll receive from your Python program into local variables:

static PyObject* factorial(PyObject* self, PyObject* args)
{
	int n;
	if (!PyArg_ParseTuple(args,"i",&n))
		return NULL;
	return Py_BuildValue("i",Cfactorial(n));
}

PyArg_ParseTuple() evaluates to false on failure. If it fails, then the function will return NULL and not proceed any further.

Writing the Init Function
You’ve written the code that makes up the core functionality of your Python C extension module. However, there are still a few extra functions that are necessary to get your module up and running. You’ll need to write definitions of your module and the methods it contains, like so:

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

PyMODINIT_FUNC
Now that you’ve defined your Python C extension module and method structures, it’s time to put them to use. When a Python program imports your module for the first time, it will call PyInit_myModule():

PyMODINIT_FUNC PyInit_myModule(void)
{
	return PyModule_Create(&myModule);
}

PyMODINIT_FUNC does 3 things implicitly when stated as the function return type:

It implicitly sets the return type of the function as PyObject*.
It declares any special linkages.
It declares the function as extern “C.” In case you’re using C++, it tells the C++ compiler not to do name-mangling on the symbols.
PyModule_Create() will return a new module object of type PyObject *. 
