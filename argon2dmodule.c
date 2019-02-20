#include <Python.h>
#include "argon2d.h"

static PyObject *argon2d_getpowhash(PyObject *self, PyObject *args)
{
    char *output;
    PyObject *value;
#if PY_MAJOR_VERSION >= 3
    PyBytesObject *input;
#else
    PyStringObject *input;
#endif
    if (!PyArg_ParseTuple(args, "S", &input))
        return NULL;
    Py_INCREF(input);
    output = PyMem_Malloc(32);
#if PY_MAJOR_VERSION >= 3
    argon2d_hash((char *)PyBytes_AsString((PyObject*) input), output);
#else
    argon2d_hash((char *)PyString_AsString((PyObject*) input), output);
#endif
    Py_DECREF(input);
#if PY_MAJOR_VERSION >= 3
    value = Py_BuildValue("y#", output, 32);
#else
    value = Py_BuildValue("s#", output, 32);
#endif
    PyMem_Free(output);
    return value;
}

static PyMethodDef argon2dMethods[] = {
    { "getPoWHash", argon2d_getpowhash, METH_VARARGS, "Returns the proof of work hash using argon2d" },
    { NULL, NULL, 0, NULL }
};

#if PY_MAJOR_VERSION >= 3
static struct PyModuleDef argon2dModule = {
    PyModuleDef_HEAD_INIT,
    "argon2d_hash",
    "...",
    -1,
    argon2dMethods
};

PyMODINIT_FUNC PyInit_argon2d_hash(void) {
    return PyModule_Create(&argon2dModule);
}

#else

PyMODINIT_FUNC initargon2d_hash(void) {
    (void) Py_InitModule("argon2d_hash", argon2dMethods);
}
#endif
