#include <stdio.h>
/* Possible weaknesses found:
 *  'Python.h' file not found
 *  Python.h: No such file or directory
 */
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

    size = PyTuple_GET_SIZE(tuple);
    *has_none = 0;

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
    PyObject *number = NULL;
    PyObject *text = NULL;
    PyObject *tuple = NULL;
    int has_none = 0;
    int exit_status = 1;

    Py_Initialize();

    if (!Py_IsInitialized()) {
        fputs("Failed to initialize Python\n", stderr);
        return 1;
    }

    number = PyLong_FromLong(1);
    if (number == NULL) {
        PyErr_Print();
        goto cleanup;
    }

    text = PyUnicode_FromString("value");
    if (text == NULL) {
        PyErr_Print();
        goto cleanup;
    }

    tuple = PyTuple_Pack(3, number, Py_None, text);
    if (tuple == NULL) {
        PyErr_Print();
        goto cleanup;
    }

    if (tuple_has_none(tuple, &has_none) < 0) {
        PyErr_Print();
        goto cleanup;
    }

    puts(has_none ? "true" : "false");
    exit_status = 0;

cleanup:
    Py_XDECREF(tuple);
    Py_XDECREF(text);
    Py_XDECREF(number);

    if (Py_FinalizeEx() < 0) {
        exit_status = 1;
    }

    return exit_status;
}