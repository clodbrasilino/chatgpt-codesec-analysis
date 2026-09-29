#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <stdio.h>
#include <stdlib.h>

static PyObject *add_dict_to_tuple(PyObject *tuple, Py_ssize_t index, PyObject *dict)
{
    Py_ssize_t size;
    Py_ssize_t i;
    PyObject *new_tuple;
    PyObject *item;

    if (tuple == NULL || dict == NULL) {
        PyErr_SetString(PyExc_ValueError, "tuple and dict must not be NULL");
        return NULL;
    }

    if (!PyTuple_Check(tuple)) {
        PyErr_SetString(PyExc_TypeError, "first argument must be a tuple");
        return NULL;
    }

    if (!PyDict_Check(dict)) {
        PyErr_SetString(PyExc_TypeError, "second argument must be a dict");
        return NULL;
    }

    size = PyTuple_Size(tuple);
    if (size < 0) {
        return NULL;
    }

    if (index < 0 || index > size) {
        PyErr_SetString(PyExc_IndexError, "index out of range");
        return NULL;
    }

    new_tuple = PyTuple_New(size + 1);
    if (new_tuple == NULL) {
        return NULL;
    }

    for (i = 0; i < index; i++) {
        item = PyTuple_GetItem(tuple, i);
        if (item == NULL) {
            Py_DECREF(new_tuple);
            return NULL;
        }
        Py_INCREF(item);
        if (PyTuple_SetItem(new_tuple, i, item) != 0) {
            Py_DECREF(new_tuple);
            return NULL;
        }
    }

    Py_INCREF(dict);
    if (PyTuple_SetItem(new_tuple, index, dict) != 0) {
        Py_DECREF(new_tuple);
        return NULL;
    }

    for (i = index; i < size; i++) {
        item = PyTuple_GetItem(tuple, i);
        if (item == NULL) {
            Py_DECREF(new_tuple);
            return NULL;
        }
        Py_INCREF(item);
        if (PyTuple_SetItem(new_tuple, i + 1, item) != 0) {
            Py_DECREF(new_tuple);
            return NULL;
        }
    }

    return new_tuple;
}

int main(void)
{
    PyObject *tuple;
    PyObject *dict;
    PyObject *key;
    PyObject *value;
    PyObject *result;
    PyObject *repr;
    const char *repr_str;

    Py_Initialize();

    tuple = Py_BuildValue("(ii)", 1, 2);
    if (tuple == NULL) {
        PyErr_Print();
        Py_Finalize();
        return EXIT_FAILURE;
    }

    dict = PyDict_New();
    if (dict == NULL) {
        Py_DECREF(tuple);
        PyErr_Print();
        Py_Finalize();
        return EXIT_FAILURE;
    }

    key = PyUnicode_FromString("language");
    if (key == NULL) {
        Py_DECREF(dict);
        Py_DECREF(tuple);
        PyErr_Print();
        Py_Finalize();
        return EXIT_FAILURE;
    }

    value = PyUnicode_FromString("C");
    if (value == NULL) {
        Py_DECREF(key);
        Py_DECREF(dict);
        Py_DECREF(tuple);
        PyErr_Print();
        Py_Finalize();
        return EXIT_FAILURE;
    }

    if (PyDict_SetItem(dict, key, value) != 0) {
        Py_DECREF(value);
        Py_DECREF(key);
        Py_DECREF(dict);
        Py_DECREF(tuple);
        PyErr_Print();
        Py_Finalize();
        return EXIT_FAILURE;
    }

    Py_DECREF(key);
    Py_DECREF(value);

    result = add_dict_to_tuple(tuple, 2, dict);
    Py_DECREF(dict);
    Py_DECREF(tuple);

    if (result == NULL) {
        PyErr_Print();
        Py_Finalize();
        return EXIT_FAILURE;
    }

    repr = PyObject_Repr(result);
    if (repr == NULL) {
        Py_DECREF(result);
        PyErr_Print();
        Py_Finalize();
        return EXIT_FAILURE;
    }

    repr_str = PyUnicode_AsUTF8(repr);
    if (repr_str == NULL) {
        Py_DECREF(repr);
        Py_DECREF(result);
        PyErr_Print();
        Py_Finalize();
        return EXIT_FAILURE;
    }

    if (printf("%s\n", repr_str) < 0) {
        Py_DECREF(repr);
        Py_DECREF(result);
        Py_Finalize();
        return EXIT_FAILURE;
    }

    Py_DECREF(repr);
    Py_DECREF(result);

    if (Py_FinalizeEx() < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}