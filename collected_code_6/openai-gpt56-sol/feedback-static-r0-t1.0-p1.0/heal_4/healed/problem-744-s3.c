#include <stdio.h>
#include <Python.h>

static int tuple_has_none(const PyObject *tuple, int *has_none)
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
        const PyObject *item = PyTuple_GET_ITEM(tuple, i);

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
    PyObject *item = NULL;
    int has_none = 0;
    int exit_status = 1;

    Py_Initialize();

    tuple = PyTuple_New(3);
    if (tuple == NULL) {
        PyErr_Print();
        goto cleanup;
    }

    item = PyLong_FromLong(1);
    if (item == NULL) {
        PyErr_Print();
        goto cleanup;
    }

    if (PyTuple_SetItem(tuple, 0, item) < 0) {
        PyErr_Print();
        goto cleanup;
    }
    item = NULL;

    item = Py_NewRef(Py_None);
    if (PyTuple_SetItem(tuple, 1, item) < 0) {
        PyErr_Print();
        goto cleanup;
    }
    item = NULL;

    item = PyUnicode_FromString("value");
    if (item == NULL) {
        PyErr_Print();
        goto cleanup;
    }

    if (PyTuple_SetItem(tuple, 2, item) < 0) {
        PyErr_Print();
        goto cleanup;
    }
    item = NULL;

    if (tuple_has_none(tuple, &has_none) < 0) {
        PyErr_Print();
        goto cleanup;
    }

    if (printf("%s\n", has_none ? "true" : "false") < 0) {
        goto cleanup;
    }

    exit_status = 0;

cleanup:
    Py_XDECREF(item);
    Py_XDECREF(tuple);

    if (Py_FinalizeEx() < 0) {
        exit_status = 1;
    }

    return exit_status;
}