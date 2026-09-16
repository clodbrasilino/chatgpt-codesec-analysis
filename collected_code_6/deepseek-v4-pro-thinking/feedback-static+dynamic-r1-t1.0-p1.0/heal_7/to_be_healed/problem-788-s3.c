#if defined(__has_include) && __has_include(<Python.h>)
#include <Python.h>
#else
/* Possible weaknesses found:
 *  #error "Python.h not found, please install python-dev or equivalent"
 *  "Python.h not found, please install python-dev or equivalent"
 */
#error "Python.h not found, please install python-dev or equivalent"
#endif

#include <stdio.h>

/* Possible weaknesses found:
 *  unknown type name 'PyObject'
 */
PyObject* create_tuple(PyObject* string, PyObject* list) {
    if (string == NULL || list == NULL) {
        /* Possible weaknesses found:
         *  use of undeclared identifier 'PyExc_TypeError'
         *  call to undeclared function 'PyErr_SetString'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         */
        PyErr_SetString(PyExc_TypeError, "Arguments must not be NULL");
        return NULL;
    }
    /* Possible weaknesses found:
     *  call to undeclared function 'PyUnicode_Check'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  call to undeclared function 'PyList_Check'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    if (!PyUnicode_Check(string) || !PyList_Check(list)) {
        /* Possible weaknesses found:
         *  use of undeclared identifier 'PyExc_TypeError'
         *  call to undeclared function 'PyErr_SetString'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         */
        PyErr_SetString(PyExc_TypeError, "Expected a Unicode string and a list");
        return NULL;
    }

    /* Possible weaknesses found:
     *  use of undeclared identifier 'tuple'
     *  use of undeclared identifier 'PyObject'
     *  call to undeclared function 'PyTuple_New'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    PyObject* tuple = PyTuple_New(2);
    /* Possible weaknesses found:
     *  use of undeclared identifier 'tuple'
     */
    if (tuple == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     *  call to undeclared function 'Py_INCREF'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    Py_INCREF(string);
    Py_INCREF(list);
    /* Possible weaknesses found:
     *  use of undeclared identifier 'tuple'
     *  call to undeclared function 'PyTuple_SET_ITEM'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    PyTuple_SET_ITEM(tuple, 0, string);
    /* Possible weaknesses found:
     *  use of undeclared identifier 'tuple'
     */
    PyTuple_SET_ITEM(tuple, 1, list);

    /* Possible weaknesses found:
     *  use of undeclared identifier 'tuple'
     */
    return tuple;
}

int main(void) {
    /* Possible weaknesses found:
     *  implicit declaration of function 'Py_Initialize' [-Wimplicit-function-declaration]
     */
    Py_Initialize();

    /* Possible weaknesses found:
     *  initialization of 'int *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
     *  unknown type name 'PyObject'
     *  implicit declaration of function 'PyUnicode_FromString' [-Wimplicit-function-declaration]
     */
    PyObject* string = PyUnicode_FromString("hello");
    if (string == NULL) {
        /* Possible weaknesses found:
         *  implicit declaration of function 'Py_Finalize' [-Wimplicit-function-declaration]
         */
        Py_Finalize();
        return 1;
    }

    /* Possible weaknesses found:
     *  initialization of 'int *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
     *  unknown type name 'PyObject'
     *  implicit declaration of function 'PyList_New' [-Wimplicit-function-declaration]
     */
    PyObject* list = PyList_New(0);
    if (list == NULL) {
        /* Possible weaknesses found:
         *  implicit declaration of function 'Py_DECREF' [-Wimplicit-function-declaration]
         */
        Py_DECREF(string);
        Py_Finalize();
        return 1;
    }

    /* Possible weaknesses found:
     *  implicit declaration of function 'PyLong_FromLong' [-Wimplicit-function-declaration]
     *  unknown type name 'PyObject'
     *  initialization of 'int *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
     */
    PyObject* item = PyLong_FromLong(42);
    if (item == NULL) {
        Py_DECREF(string);
        Py_DECREF(list);
        Py_Finalize();
        return 1;
    }

    /* Possible weaknesses found:
     *  implicit declaration of function 'PyList_Append' [-Wimplicit-function-declaration]
     */
    if (PyList_Append(list, item) < 0) {
        Py_DECREF(item);
        Py_DECREF(string);
        Py_DECREF(list);
        Py_Finalize();
        return 1;
    }

    Py_DECREF(item);

    /* Possible weaknesses found:
     *  implicit declaration of function 'create_tuple' [-Wimplicit-function-declaration]
     *  unknown type name 'PyObject'
     *  initialization of 'int *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
     */
    PyObject* tuple = create_tuple(string, list);
    if (tuple == NULL) {
        /* Possible weaknesses found:
         *  implicit declaration of function 'PyErr_Print' [-Wimplicit-function-declaration]
         */
        PyErr_Print();
        Py_DECREF(string);
        Py_DECREF(list);
        Py_Finalize();
        return 1;
    }

    /* Possible weaknesses found:
     *  implicit declaration of function 'PyObject_Print' [-Wimplicit-function-declaration]
     */
    if (PyObject_Print(tuple, stdout, 0) < 0) {
        PyErr_Print();
    }
    printf("\n");

    Py_DECREF(tuple);
    Py_DECREF(string);
    Py_DECREF(list);
    Py_Finalize();
    return 0;
}