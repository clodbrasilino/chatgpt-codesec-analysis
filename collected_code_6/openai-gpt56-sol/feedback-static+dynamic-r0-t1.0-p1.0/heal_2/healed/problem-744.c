#include <stdio.h>
#include <Python.h>

static int tuple_has_none(PyObject *tuple, int *has_none)
{
    Py_ssize_t size;
    Py_ssize_t i;

    if (has_none == NULL) {
        PyErr_SetString(PyExc_ValueError, "result pointer must not be NULL");
        return -1;
    }

    if (tuple == NULL || !PyTuple_Check(tuple)) {
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
    PyObject *first = NULL;
    PyObject *third = NULL;
    PyObject *tuple = NULL;
    int has_none = 0;
    int status = 1;

    Py_Initialize();

    first = PyLong_FromLong(1);
    if (first == NULL) {
        goto error;
    }

    third = PyUnicode_FromString("value");
    if (third == NULL) {
        goto error;
    }

    tuple = PyTuple_Pack(3, first, Py_None, third);
    if (tuple == NULL) {
        goto error;
    }

    if (tuple_has_none(tuple, &has_none) < 0) {
        goto error;
    }

    if (printf("%s\n", has_none ? "true" : "false") < 0) {
        goto cleanup;
    }

    status = 0;
    goto cleanup;

error:
    PyErr_Print();

cleanup:
    Py_XDECREF(tuple);
    Py_XDECREF(third);
    Py_XDECREF(first);

    if (Py_FinalizeEx() < 0) {
        status = 1;
    }

    return status;
}