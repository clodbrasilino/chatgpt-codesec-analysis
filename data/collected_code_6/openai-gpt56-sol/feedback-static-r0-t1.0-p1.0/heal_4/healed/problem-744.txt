#include <Python.h>
#include <stdio.h>

static int tuple_has_none(const PyObject *tuple, int *has_none)
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
    size = PyTuple_Size((PyObject *)tuple);
    if (size < 0) {
        return -1;
    }

    for (i = 0; i < size; ++i) {
        const PyObject *item = PyTuple_GetItem((PyObject *)tuple, i);

        if (item == NULL) {
            return -1;
        }

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
    PyObject *number = NULL;
    PyObject *text = NULL;
    int has_none = 0;
    int status = 1;

    Py_Initialize();

    number = PyLong_FromLong(1);
    if (number == NULL) {
        goto error;
    }

    text = PyUnicode_FromString("value");
    if (text == NULL) {
        goto error;
    }

    tuple = PyTuple_Pack(3, number, Py_None, text);
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
    Py_XDECREF(text);
    Py_XDECREF(number);

    if (Py_FinalizeEx() < 0) {
        status = 1;
    }

    return status;
}