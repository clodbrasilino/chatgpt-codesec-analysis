#include <stdio.h>
#include <stdlib.h>

double multiply_and_divide(const double *list, size_t length, int *error)
{
    double product = 1.0;
    size_t i;

    if (list == NULL || length == 0U || error == NULL) {
        if (error != NULL) {
            *error = 1;
        }
        return 0.0;
    }

    *error = 0;

    for (i = 0U; i < length; i++) {
        product *= list[i];
    }

    return product / (double)length;
}

int main(void)
{
    double numbers[] = { 2.0, 3.0, 4.0, 5.0 };
    size_t length = sizeof(numbers) / sizeof(numbers[0]);
    int error = 0;
    double result;

    result = multiply_and_divide(numbers, length, &error);

    if (error != 0) {
        if (fprintf(stderr, "Error: invalid input\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("Result: %f\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}