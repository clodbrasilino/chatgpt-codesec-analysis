#define PY_SSIZE_T_CLEAN

#if defined(__has_include)
#  if __has_include(<Python.h>)
#    include <Python.h>
#  elif __has_include(<python3.12/Python.h>)
#    include <python3.12/Python.h>
#  elif __has_include(<python3.11/Python.h>)
#    include <python3.11/Python.h>
#  elif __has_include(<python3.10/Python.h>)
#    include <python3.10/Python.h>
#  elif __has_include(<python3.9/Python.h>)
#    include <python3.9/Python.h>
#  elif __has_include(<python3.8/Python.h>)
#    include <python3.8/Python.h>
#  else
/* Possible weaknesses found:
 *  "Python development headers not found. Install python3-dev (Debian/Ubuntu) or python3-devel (Fedora/RHEL) and compile with: cc $(python3-config --cflags) file.c $(python3-config --ldflags --embed)"
 *  #error "Python development headers not found. Install python3-dev (Debian/Ubuntu) or python3-devel (Fedora/RHEL) and compile with: cc $(python3-config --cflags) file.c $(python3-config --ldflags --embed)"
 */
#    error "Python development headers not found. Install python3-dev (Debian/Ubuntu) or python3-devel (Fedora/RHEL) and compile with: cc $(python3-config --cflags) file.c $(python3-config --ldflags --embed)"
#  endif
#else
#  include <Python.h>
#endif

#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  unknown type name 'PyObject'
 *  unknown type name 'Py_ssize_t'; did you mean 'ssize_t'?
 */
static int add_dict_to_tuple(PyObject *tuple, Py_ssize_t index, PyObject *dict);

/* Possible weaknesses found:
 *  unknown type name 'PyObject'
 *  unknown type name 'Py_ssize_t'; did you mean 'ssize_t'?
 */
static int add_dict_to_tuple(PyObject *tuple, Py_ssize_t index, PyObject *dict)
{
    if (tuple == NULL || dict == NULL) {
        /* Possible weaknesses found:
         *  'ssize_t' declared here
         */
        return -1;
    }

    /* Possible weaknesses found:
     *  call to undeclared function 'PyTuple_Check'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    if (!PyTuple_Check(tuple)) {
        return -1;
    }

    /* Possible weaknesses found:
     *  call to undeclared function 'PyTuple_Size'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    if (index < 0 || index >= PyTuple_Size(tuple)) {
        return -1;
    }

    /* Possible weaknesses found:
     *  call to undeclared function 'Py_INCREF'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    Py_INCREF(dict);

    /* Possible weaknesses found:
     *  call to undeclared function 'PyTuple_SetItem'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    if (PyTuple_SetItem(tuple, index, dict) != 0) {
        return -1;
    }

    return 0;
}

int main(void)
{
    int exit_status = EXIT_FAILURE;
    /* Possible weaknesses found:
     *  unknown type name 'PyObject'
     *  use of undeclared identifier 'tuple'
     *  use of undeclared identifier 'PyObject'
     */
    PyObject *tuple = NULL;
    /* Possible weaknesses found:
     *  use of undeclared identifier 'dict'
     *  unknown type name 'PyObject'
     *  use of undeclared identifier 'PyObject'
     */
    PyObject *dict = NULL;
    /* Possible weaknesses found:
     *  unknown type name 'PyObject'
     *  use of undeclared identifier 'PyObject'
     *  use of undeclared identifier 'key'
     */
    PyObject *key = NULL;
    /* Possible weaknesses found:
     *  unknown type name 'PyObject'
     *  use of undeclared identifier 'value'
     *  use of undeclared identifier 'PyObject'
     */
    PyObject *value = NULL;

    /* Possible weaknesses found:
     *  implicit declaration of function 'Py_Initialize' [-Wimplicit-function-declaration]
     */
    Py_Initialize();

    /* Possible weaknesses found:
     *  assignment to 'int *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
     *  implicit declaration of function 'PyTuple_New' [-Wimplicit-function-declaration]
     */
    tuple = PyTuple_New(1);
    if (tuple == NULL) {
        goto cleanup;
    }

    /* Possible weaknesses found:
     *  assignment to 'int *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
     *  implicit declaration of function 'PyDict_New' [-Wimplicit-function-declaration]
     */
    dict = PyDict_New();
    if (dict == NULL) {
        goto cleanup;
    }

    /* Possible weaknesses found:
     *  assignment to 'int *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
     *  implicit declaration of function 'PyUnicode_FromString' [-Wimplicit-function-declaration]
     */
    key = PyUnicode_FromString("language");
    if (key == NULL) {
        goto cleanup;
    }

    /* Possible weaknesses found:
     *  assignment to 'int *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
     */
    value = PyUnicode_FromString("C");
    if (value == NULL) {
        goto cleanup;
    }

    /* Possible weaknesses found:
     *  implicit declaration of function 'PyDict_SetItem' [-Wimplicit-function-declaration]
     */
    if (PyDict_SetItem(dict, key, value) != 0) {
        goto cleanup;
    }

    /* Possible weaknesses found:
     *  implicit declaration of function 'add_dict_to_tuple' [-Wimplicit-function-declaration]
     */
    if (add_dict_to_tuple(tuple, 0, dict) != 0) {
        goto cleanup;
    }

    /* Possible weaknesses found:
     *  implicit declaration of function 'PyObject_Print' [-Wimplicit-function-declaration]
     */
    if (PyObject_Print(tuple, stdout, 0) != 0) {
        goto cleanup;
    }

    if (fputc('\n', stdout) == EOF) {
        goto cleanup;
    }

    exit_status = EXIT_SUCCESS;

cleanup:
    /* Possible weaknesses found:
     *  implicit declaration of function 'Py_XDECREF' [-Wimplicit-function-declaration]
     */
    Py_XDECREF(key);
    Py_XDECREF(value);
    Py_XDECREF(dict);
    Py_XDECREF(tuple);

    /* Possible weaknesses found:
     *  implicit declaration of function 'PyErr_Occurred' [-Wimplicit-function-declaration]
     */
    if (PyErr_Occurred()) {
        /* Possible weaknesses found:
         *  implicit declaration of function 'PyErr_Print' [-Wimplicit-function-declaration]
         */
        PyErr_Print();
    }

    /* Possible weaknesses found:
     *  implicit declaration of function 'Py_FinalizeEx' [-Wimplicit-function-declaration]
     */
    if (Py_FinalizeEx() < 0) {
        exit_status = EXIT_FAILURE;
    }

    return exit_status;
}