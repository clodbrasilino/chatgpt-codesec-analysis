#include <stdio.h>
#include <stdlib.h>

#if defined(__has_include)
#  if __has_include(<Python.h>)
#    include <Python.h>
#  elif __has_include(<python3.14/Python.h>)
#    include <python3.14/Python.h>
#  elif __has_include(<python3.13/Python.h>)
#    include <python3.13/Python.h>
#  elif __has_include(<python3.12/Python.h>)
#    include <python3.12/Python.h>
#  elif __has_include(<python3.11/Python.h>)
#    include <python3.11/Python.h>
#  elif __has_include(<python3.10/Python.h>)
#    include <python3.10/Python.h>
#  else
/* Possible weaknesses found:
 *  #error "Python development headers not found"
 *  "Python development headers not found"
 */
#    error "Python development headers not found"
#  endif
#else
#  include <Python.h>
#endif

/* Possible weaknesses found:
 *  unknown type name 'PyObject'
 */
static int tuple_has_none(PyObject *tuple, int *has_none)
{
    /* Possible weaknesses found:
     *  unknown type name 'Py_ssize_t'; did you mean 'ssize_t'?
     */
    Py_ssize_t size;
    /* Possible weaknesses found:
     *  unknown type name 'Py_ssize_t'; did you mean 'ssize_t'?
     */
    Py_ssize_t i;

    if (has_none == NULL) {
        /* Possible weaknesses found:
         *  call to undeclared function 'PyErr_SetString'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  use of undeclared identifier 'PyExc_ValueError'
         */
        PyErr_SetString(PyExc_ValueError, "result pointer must not be NULL");
        /* Possible weaknesses found:
         *  'ssize_t' declared here
         */
        return -1;
    }

    /* Possible weaknesses found:
     *  call to undeclared function 'PyTuple_Check'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    if (tuple == NULL || !PyTuple_Check(tuple)) {
        /* Possible weaknesses found:
         *  use of undeclared identifier 'PyExc_TypeError'
         *  call to undeclared function 'PyErr_SetString'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         */
        PyErr_SetString(PyExc_TypeError, "expected a tuple");
        return -1;
    }

    *has_none = 0;
    /* Possible weaknesses found:
     *  call to undeclared function 'PyTuple_Size'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    size = PyTuple_Size(tuple);
    if (size < 0) {
        return -1;
    }

    for (i = 0; i < size; ++i) {
        /* Possible weaknesses found:
         *  use of undeclared identifier 'item'
         *  Variable 'item' can be declared as pointer to const [constVariablePointer]
         *  use of undeclared identifier 'PyObject'
         *  call to undeclared function 'PyTuple_GetItem'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         */
        PyObject *item = PyTuple_GetItem(tuple, i);

        /* Possible weaknesses found:
         *  use of undeclared identifier 'item'
         */
        if (item == NULL) {
            return -1;
        }

        /* Possible weaknesses found:
         *  use of undeclared identifier 'item'
         *  use of undeclared identifier 'Py_None'
         */
        if (item == Py_None) {
            *has_none = 1;
            break;
        }
    }

    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     *  use of undeclared identifier 'tuple'
     *  use of undeclared identifier 'PyObject'
     *  unknown type name 'PyObject'
     */
    PyObject *tuple = NULL;
    /* Possible weaknesses found:
     *  use of undeclared identifier 'PyObject'
     *  unknown type name 'PyObject'
     */
    PyObject *number = NULL;
    /* Possible weaknesses found:
     *  unknown type name 'PyObject'
     */
    PyObject *text = NULL;
    int has_none = 0;
    int status = EXIT_FAILURE;

    /* Possible weaknesses found:
     *  implicit declaration of function 'Py_Initialize' [-Wimplicit-function-declaration]
     */
    Py_Initialize();

    /* Possible weaknesses found:
     *  implicit declaration of function 'PyLong_FromLong' [-Wimplicit-function-declaration]
     *  assignment to 'int *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
     */
    number = PyLong_FromLong(1);
    if (number == NULL) {
        goto error;
    }

    /* Possible weaknesses found:
     *  implicit declaration of function 'PyUnicode_FromString' [-Wimplicit-function-declaration]
     *  assignment to 'int *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
     */
    text = PyUnicode_FromString("value");
    if (text == NULL) {
        goto error;
    }

    /* Possible weaknesses found:
     *  implicit declaration of function 'PyTuple_Pack' [-Wimplicit-function-declaration]
     *  'Py_None' undeclared (first use in this function)
     *  each undeclared identifier is reported only once for each function it appears in
     */
    tuple = PyTuple_Pack(3, number, Py_None, text);
    if (tuple == NULL) {
        goto error;
    }

    /* Possible weaknesses found:
     *  implicit declaration of function 'tuple_has_none' [-Wimplicit-function-declaration]
     */
    if (tuple_has_none(tuple, &has_none) < 0) {
        goto error;
    }

    if (printf("%s\n", has_none ? "true" : "false") < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;
    goto cleanup;

error:
    /* Possible weaknesses found:
     *  implicit declaration of function 'PyErr_Occurred' [-Wimplicit-function-declaration]
     */
    if (PyErr_Occurred()) {
        /* Possible weaknesses found:
         *  implicit declaration of function 'PyErr_Print' [-Wimplicit-function-declaration]
         */
        PyErr_Print();
    }

cleanup:
    /* Possible weaknesses found:
     *  implicit declaration of function 'Py_XDECREF' [-Wimplicit-function-declaration]
     */
    Py_XDECREF(tuple);
    Py_XDECREF(text);
    Py_XDECREF(number);

    /* Possible weaknesses found:
     *  implicit declaration of function 'Py_FinalizeEx' [-Wimplicit-function-declaration]
     */
    if (Py_FinalizeEx() < 0) {
        status = EXIT_FAILURE;
    }

    return status;
}