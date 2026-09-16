#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

double multiply_and_divide(const double *list, size_t length);

double multiply_and_divide(const double *list, size_t length) {
    double product = 1.0;
    size_t i;

    if (list == NULL || length == 0) {
        return 0.0;
    }

    for (i = 0; i < length; i++) {
        product *= list[i];
    }

    return product / (double)length;
}

int main(void) {
    const double numbers[] = {2.0, 4.0, 6.0, 8.0};
    size_t length = sizeof(numbers) / sizeof(numbers[0]);
    double result;

    result = multiply_and_divide(numbers, length);

    printf("%f\n", result);

    return EXIT_SUCCESS;
}