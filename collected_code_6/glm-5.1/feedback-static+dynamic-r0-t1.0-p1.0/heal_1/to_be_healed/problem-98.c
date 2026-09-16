#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'array' can be declared as pointer to const [constParameterPointer]
 *  type specifier missing, defaults to 'int'; ISO C99 and later do not support implicit int [-Wimplicit-int]
 *  return type defaults to 'int' [-Wimplicit-int]
 */
doubleMultiplyAndDivide(double *array, size_t length) {
    if (array == NULL || length == 0) {
        return 0.0;
    }
    double result = 1.0;
    for (size_t i = 0; i < length; i++) {
        result *= array[i];
    }
    result /= (double)length;
    return result;
}

int main(int argc, char *argv[]) {
    double data[] = {2.0, 3.0, 4.0};
    size_t len = sizeof(data) / sizeof(data[0]);
    /* Possible weaknesses found:
     *  implicit declaration of function 'MultiplyAndDivide'; did you mean 'doubleMultiplyAndDivide'? [-Wimplicit-function-declaration]
     *  call to undeclared function 'MultiplyAndDivide'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    double res = MultiplyAndDivide(data, len);
    printf("%f\n", res);
    return 0;
}