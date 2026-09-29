#include <Python.h>
#include <stdio.h>

static int tuple_has_none(PyObject *tuple, int *has_none)
{
    Py_ssize_t size;
    Py_ssize_t i;

    if (tuple == NULL || has_none == NULL) {
        PyErr_SetString(PyExc_ValueError, "invalid argument");
        return -1;
    }

    if (!PyTuple_Check(tuple)) {
        PyErr_SetString(PyExc_TypeError, "expected a tuple");
        return -1;
    }

    *has_none = 0;
    size = PyTuple_GET_SIZE(tuple);

    for (i = 0; i < size; ++i) {
        PyObject *item = PyTuple_GET_ITEM(tuple, i);

        if (item == Py_None) {
            *has_none = 1;
            break;
        }
    }

    return 0;
}

int main(void)
{
    PyObject *tuple = NULL;
    int has_none = 0;
    int exit_status = 1;

    Py_Initialize();

    tuple = PyTuple_New(3);
    if (tuple == NULL) {
        PyErr_Print();
        goto cleanup;
    }

    if (PyTuple_SetItem(tuple, 0, PyLong_FromLong(1)) < 0) {
        PyErr_Print();
        goto cleanup;
    }

    Py_INCREF(Py_None);
    if (PyTuple_SetItem(tuple, 1, Py_None) < 0) {
        Py_DECREF(Py_None);
        PyErr_Print();
        goto cleanup;
    }

    if (PyTuple_SetItem(tuple, 2, PyUnicode_FromString("value")) < 0) {
        PyErr_Print();
        goto cleanup;
    }

    if (tuple_has_none(tuple, &has_none) < 0) {
        PyErr_Print();
        goto cleanup;
    }

    printf("%s\n", has_none ? "true" : "false");
    exit_status = 0;

cleanup:
    Py_XDECREF(tuple);

    if (Py_FinalizeEx() < 0) {
        exit_status = 1;
    }

    return exit_status;
}