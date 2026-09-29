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

    if (tuple == NULL || has_none == NULL) {
        PyErr_SetString(PyExc_ValueError, "invalid argument");
        return -1;
    }

    if (!PyTuple_Check(tuple)) {
        PyErr_SetString(PyExc_TypeError, "expected a tuple");
        return -1;
    }

    size = PyTuple_Size(tuple);
    if (size < 0) {
        return -1;
    }

    *has_none = 0;

    for (i = 0; i < size; ++i) {
        /* Possible weaknesses found:
         *  Variable 'item' can be declared as pointer to const [constVariablePointer]
         */
        PyObject *item = PyTuple_GetItem(tuple, i);

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
    int has_none = 0;
    int exit_status = 1;

    Py_Initialize();

    if (!Py_IsInitialized()) {
        fputs("Failed to initialize Python\n", stderr);
        return 1;
    }

    tuple = PyTuple_Pack(3, PyLong_FromLong(1), Py_None, PyUnicode_FromString("value"));
    if (tuple == NULL) {
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