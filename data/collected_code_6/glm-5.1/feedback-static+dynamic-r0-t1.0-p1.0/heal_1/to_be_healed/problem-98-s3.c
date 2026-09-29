#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'array' can be declared as pointer to const [constParameterPointer]
 */
double calculate(double *array, size_t length) {
    if (array == NULL || length == 0) {
        return 0.0;
    }

    double product = 1.0;
    for (size_t i = 0; i < length; i++) {
        product *= array[i];
    }

    return product / length;
}

int main(void) {
    double data[] = {2.0, 4.0, 6.0, 8.0};
    size_t length = sizeof(data) / sizeof(data[0]);

    double result = calculate(data, length);
    printf("%f\n", result);

    return 0;
}