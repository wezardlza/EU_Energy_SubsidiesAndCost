/*----------------------------------------------------------------------------------------------------------------------
Sumamry: A CPP built-in function is called in this script.
----------------------------------------------------------------------------------------------------------------------*/
extern "C" {
#include<Python.h>

	static PyObject *EU_Energy_SubsidiesAndCostError;

	static PyObject *


		EU_Energy_SubsidiesAndCost_system(PyObject *self, PyObject *args)
	{
		const char *command;
		int sts;

		if (!PyArg_ParseTuple(args, "s", &command))
			return NULL;
		sts = system(command);
		if (sts < 0) {
			PyErr_SetString(EU_Energy_SubsidiesAndCostError, "System command failed");
			return NULL;
		}
		return PyLong_FromLong(sts);
	}

	static PyMethodDef EU_Energy_SubsidiesAndCostMethods[] = {
		{"system",  EU_Energy_SubsidiesAndCost_system, METH_VARARGS,
		"Execute a shell command."},
		{NULL, NULL, 0, NULL}        /* Sentinel */
	};

	static struct PyModuleDef EU_Energy_SubsidiesAndCostmodule = {
		PyModuleDef_HEAD_INIT,
		"EU_Energy_SubsidiesAndCost",   /* name of module */
		NULL,     /* module documentation, may be NULL */
		-1,       /* size of per-interpreter state of the module,
				  or -1 if the module keeps state in global variables. */
		EU_Energy_SubsidiesAndCostMethods
	};

	PyMODINIT_FUNC
		PyInit_EU_Energy_SubsidiesAndCost(void)
	{
		PyObject *m;

		m = PyModule_Create(&EU_Energy_SubsidiesAndCostmodule);
		if (m == NULL)
			return NULL;

		EU_Energy_SubsidiesAndCostError = PyErr_NewException("EU_Energy_SubsidiesAndCost.error", NULL, NULL);
		Py_INCREF(EU_Energy_SubsidiesAndCostError);
		PyModule_AddObject(m, "error", EU_Energy_SubsidiesAndCostError);
		return m;
	}

	int main(int argc, char *argv[])
	{
		wchar_t *program = Py_DecodeLocale(argv[0], NULL);
		if (program == NULL) {
			fprintf(stderr, "Fatal error: cannot decode argv[0]\n");
			exit(1);
		}

		/* Add a built-in module, before Py_Initialize */
		PyImport_AppendInittab("EU_Energy_SubsidiesAndCost", PyInit_EU_Energy_SubsidiesAndCost);

		/* Pass argv[0] to the Python interpreter */
		Py_SetProgramName(program);

		/* Initialize the Python interpreter.  Required. */
		Py_Initialize();

		/* Optionally import the module; alternatively,
		import can be deferred until the embedded script
		imports it. */
		PyImport_ImportModule("EU_Energy_SubsidiesAndCost");

		PyMem_RawFree(program);

		return 0;
	}
}