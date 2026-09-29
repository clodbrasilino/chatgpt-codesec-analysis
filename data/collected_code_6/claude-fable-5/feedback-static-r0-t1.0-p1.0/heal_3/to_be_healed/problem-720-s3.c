#define PY_SSIZE_T_CLEAN

#if defined(__has_include)
#if __has_include(<Python.h>)
#include <Python.h>
#else
/* Possible weaknesses found:
 *  "Python.h not found: install the Python development headers (e.g. python3-dev) and compile with the correct include path (python3-config --includes)"
 *  #error "Python.h not found: install the Python development headers (e.g. python3-dev) and compile with the correct include path (python3-config --includes)"
 */
#error "Python.h not found: install the Python development headers (e.g. python3-dev) and compile with the correct include path (python3-config --includes)"
#endif
#else
#include <Python.h>
#endif

#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  unknown type name 'PyObject'
 *  unknown type name 'Py_ssize_t'; did you mean 'ssize_t'?
 */
static PyObject *add_dict_to_tuple(PyObject *tuple, Py_ssize_t index, PyObject *dict)
{
    /* Possible weaknesses found:
     *  unknown type name 'Py_ssize_t'; did you mean 'ssize_t'?
     */
    Py_ssize_t size;
    /* Possible weaknesses found:
     *  unknown type name 'Py_ssize_t'; did you mean 'ssize_t'?
     */
    Py_ssize_t i;
    /* Possible weaknesses found:
     *  use of undeclared identifier 'new_tuple'
     *  use of undeclared identifier 'PyObject'
     */
    PyObject *new_tuple;
    /* Possible weaknesses found:
     *  use of undeclared identifier 'PyObject'
     *  use of undeclared identifier 'item'
     */
    PyObject *item;

    if (tuple == NULL || dict == NULL) {
        /* Possible weaknesses found:
         *  call to undeclared function 'PyErr_SetString'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  use of undeclared identifier 'PyExc_ValueError'
         */
        PyErr_SetString(PyExc_ValueError, "tuple and dict must not be NULL");
        return NULL;
    }

    /* Possible weaknesses found:
     *  call to undeclared function 'PyTuple_Check'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    if (!PyTuple_Check(tuple)) {
        /* Possible weaknesses found:
         *  use of undeclared identifier 'PyExc_TypeError'
         *  call to undeclared function 'PyErr_SetString'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         */
        PyErr_SetString(PyExc_TypeError, "first argument must be a tuple");
        return NULL;
    /* Possible weaknesses found:
     *  'ssize_t' declared here
     */
    }

    /* Possible weaknesses found:
     *  call to undeclared function 'PyDict_Check'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    if (!PyDict_Check(dict)) {
        /* Possible weaknesses found:
         *  use of undeclared identifier 'PyExc_TypeError'
         *  call to undeclared function 'PyErr_SetString'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         */
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
    /* Possible weaknesses found:
     *  unknown type name 'PyObject'
     */
    PyObject *tuple;
    /* Possible weaknesses found:
     *  unknown type name 'PyObject'
     */
    PyObject *dict;
    /* Possible weaknesses found:
     *  unknown type name 'PyObject'
     */
    PyObject *key;
    /* Possible weaknesses found:
     *  unknown type name 'PyObject'
     */
    PyObject *value;
    /* Possible weaknesses found:
     *  unknown type name 'PyObject'
     */
    PyObject *result;
    /* Possible weaknesses found:
     *  unknown type name 'PyObject'
     */
    PyObject *repr;
    const char *repr_str;

    /* Possible weaknesses found:
     *  implicit declaration of function 'Py_Initialize' [-Wimplicit-function-declaration]
     */
    Py_Initialize();

    /* Possible weaknesses found:
     *  assignment to 'int *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
     *  implicit declaration of function 'Py_BuildValue' [-Wimplicit-function-declaration]
     */
    tuple = Py_BuildValue("(ii)", 1, 2);
    if (tuple == NULL) {
        /* Possible weaknesses found:
         *  implicit declaration of function 'PyErr_Print' [-Wimplicit-function-declaration]
         */
        PyErr_Print();
        /* Possible weaknesses found:
         *  implicit declaration of function 'Py_Finalize' [-Wimplicit-function-declaration]
         */
        Py_Finalize();
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     *  assignment to 'int *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
     *  implicit declaration of function 'PyDict_New' [-Wimplicit-function-declaration]
     */
    dict = PyDict_New();
    if (dict == NULL) {
        /* Possible weaknesses found:
         *  implicit declaration of function 'Py_DECREF' [-Wimplicit-function-declaration]
         */
        Py_DECREF(tuple);
        PyErr_Print();
        Py_Finalize();
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     *  assignment to 'int *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
     *  implicit declaration of function 'PyUnicode_FromString' [-Wimplicit-function-declaration]
     */
    key = PyUnicode_FromString("language");
    if (key == NULL) {
        Py_DECREF(dict);
        Py_DECREF(tuple);
        PyErr_Print();
        Py_Finalize();
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     *  assignment to 'int *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
     */
    value = PyUnicode_FromString("C");
    if (value == NULL) {
        Py_DECREF(key);
        Py_DECREF(dict);
        Py_DECREF(tuple);
        PyErr_Print();
        Py_Finalize();
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     *  implicit declaration of function 'PyDict_SetItem' [-Wimplicit-function-declaration]
     */
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

    /* Possible weaknesses found:
     *  assignment to 'int *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
     *  implicit declaration of function 'add_dict_to_tuple' [-Wimplicit-function-declaration]
     */
    result = add_dict_to_tuple(tuple, 2, dict);
    Py_DECREF(dict);
    Py_DECREF(tuple);

    if (result == NULL) {
        PyErr_Print();
        Py_Finalize();
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     *  assignment to 'int *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
     *  implicit declaration of function 'PyObject_Repr' [-Wimplicit-function-declaration]
     */
    repr = PyObject_Repr(result);
    if (repr == NULL) {
        Py_DECREF(result);
        PyErr_Print();
        Py_Finalize();
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     *  implicit declaration of function 'PyUnicode_AsUTF8' [-Wimplicit-function-declaration]
     *  assignment to 'const char *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
     */
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

    /* Possible weaknesses found:
     *  implicit declaration of function 'Py_FinalizeEx' [-Wimplicit-function-declaration]
     */
    if (Py_FinalizeEx() < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}