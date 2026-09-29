/* Possible weaknesses found:
 *  'Python.h' file not found
 *  Python.h: No such file or directory
 */
#include <Python.h>
#include <stdio.h>
#include <stdlib.h>

static int add_dict_to_tuple(PyObject *tuple, Py_ssize_t index, PyObject *dict)
{
    if (tuple == NULL || dict == NULL) {
        return -1;
    }

    if (!PyTuple_Check(tuple) || !PyDict_Check(dict)) {
        return -1;
    }

    if (index < 0 || index >= PyTuple_Size(tuple)) {
        return -1;
    }

    Py_INCREF(dict);
    if (PyTuple_SetItem(tuple, index, dict) != 0) {
        Py_DECREF(dict);
        return -1;
    }

    return 0;
}

int main(void)
{
    PyObject *tuple = NULL;
    PyObject *dict = NULL;
    PyObject *key = NULL;
    PyObject *value = NULL;
    int status = EXIT_FAILURE;

    Py_Initialize();

    tuple = PyTuple_New(1);
    if (tuple == NULL) {
        goto cleanup;
    }

    dict = PyDict_New();
    if (dict == NULL) {
        goto cleanup;
    }

    key = PyUnicode_FromString("language");
    if (key == NULL) {
        goto cleanup;
    }

    value = PyUnicode_FromString("C");
    if (value == NULL) {
        goto cleanup;
    }

    if (PyDict_SetItem(dict, key, value) != 0) {
        goto cleanup;
    }

    if (add_dict_to_tuple(tuple, 0, dict) != 0) {
        goto cleanup;
    }

    if (PyObject_Print(tuple, stdout, 0) != 0) {
        goto cleanup;
    }
    printf("\n");

    status = EXIT_SUCCESS;

cleanup:
    Py_XDECREF(value);
    Py_XDECREF(key);
    Py_XDECREF(dict);
    Py_XDECREF(tuple);

    if (PyErr_Occurred()) {
        PyErr_Print();
    }

    if (Py_FinalizeEx() < 0) {
        status = EXIT_FAILURE;
    }

    return status;
}