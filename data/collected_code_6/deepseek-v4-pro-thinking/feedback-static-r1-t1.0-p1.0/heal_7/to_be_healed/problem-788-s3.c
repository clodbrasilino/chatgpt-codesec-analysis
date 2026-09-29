/* Possible weaknesses found:
 *  'Python.h' file not found
 *  Python.h: No such file or directory
 */
#include <Python.h>
#include <stdio.h>

PyObject* create_tuple(PyObject* string, PyObject* list) {
    if (string == NULL || list == NULL) {
        PyErr_SetString(PyExc_TypeError, "Arguments must not be NULL");
        return NULL;
    }
    if (!PyUnicode_Check(string) || !PyList_Check(list)) {
        PyErr_SetString(PyExc_TypeError, "Expected a Unicode string and a list");
        return NULL;
    }

    return PyTuple_Pack(2, string, list);
}

int main(void) {
    Py_Initialize();

    PyObject *string = NULL;
    PyObject *list = NULL;
    PyObject *item = NULL;
    PyObject *tuple = NULL;
    int ret = 1;

    string = PyUnicode_FromString("hello");
    if (string == NULL) {
        goto error;
    }

    list = PyList_New(0);
    if (list == NULL) {
        goto error;
    }

    item = PyLong_FromLong(42);
    if (item == NULL) {
        goto error;
    }

    if (PyList_Append(list, item) < 0) {
        goto error;
    }

    Py_DECREF(item);
    item = NULL;

    tuple = create_tuple(string, list);
    if (tuple == NULL) {
        goto error;
    }

    if (PyObject_Print(tuple, stdout, 0) < 0) {
        goto error;
    }
    printf("\n");

    ret = 0;
    goto cleanup;

error:
    PyErr_Print();

cleanup:
    Py_XDECREF(tuple);
    Py_XDECREF(item);
    Py_XDECREF(list);
    Py_XDECREF(string);
    Py_Finalize();
    return ret;
}