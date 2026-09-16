#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static int multiply_and_divide(const double *numbers, size_t length, double *result)
{
    double product;
    size_t i;

    if (numbers == NULL || result == NULL || length == 0U) {
        return -1;
    }

    product = 1.0;
    for (i = 0U; i < length; i++) {
        product *= numbers[i];
        if (isinf(product) || isnan(product)) {
            return -1;
        }
    }

    *result = product / (double)length;

    if (isinf(*result) || isnan(*result)) {
        return -1;
    }

    return 0;
}

int main(void)
{
    double values[] = { 2.0, 3.0, 4.0, 5.0 };
    size_t count = sizeof(values) / sizeof(values[0]);
    double result = 0.0;

    if (multiply_and_divide(values, count, &result) != 0) {
        (void)fprintf(stderr, "Error: computation failed\n");
        return EXIT_FAILURE;
    }

    if (printf("Result: %f\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}