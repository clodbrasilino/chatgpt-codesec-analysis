/* Possible weaknesses found:
 *  'Python.h' file not found
 *  Python.h: No such file or directory
 */
#include <Python.h>
#include <stdio.h>

static int tuple_has_none(PyObject *tuple, int *has_none)
{
    Py_ssize_t size;
    Py_ssize_t i;

    if (tuple == NULL || has_none == NULL || !PyTuple_Check(tuple)) {
        PyErr_SetString(PyExc_TypeError, "expected a tuple and a valid result pointer");
        return -1;
    }

    *has_none = 0;
    size = PyTuple_GET_SIZE(tuple);

    for (i = 0; i < size; ++i) {
        if (PyTuple_GET_ITEM(tuple, i) == Py_None) {
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
    int status = 1;

    Py_Initialize();

    tuple = PyTuple_Pack(3, PyLong_FromLong(1), Py_None, PyUnicode_FromString("value"));
    if (tuple == NULL) {
        PyErr_Print();
        goto cleanup;
    }

    if (tuple_has_none(tuple, &has_none) != 0) {
        PyErr_Print();
        goto cleanup;
    }

    printf("%s\n", has_none ? "true" : "false");
    status = 0;

cleanup:
    Py_XDECREF(tuple);

    if (Py_FinalizeEx() < 0) {
        status = 1;
    }

    return status;
}