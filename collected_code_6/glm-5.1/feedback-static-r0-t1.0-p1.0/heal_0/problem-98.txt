#include <stdio.h>
#include <stdlib.h>

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
    double res = MultiplyAndDivide(data, len);
    printf("%f\n", res);
    return 0;
}