#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

enum { MAX_VALUES = 1000000 };

static int calculate_average(const double values[], size_t count, double *average)
{
    if (values == NULL || average == NULL || count == 0U) {
        return 0;
    }

    double sum = 0.0;

    for (size_t i = 0U; i < count; ++i) {
        sum += values[i];
    }

    *average = sum / (double)count;
    return 1;
}

int main(void)
{
    size_t count = 0U;

    if (scanf("%zu", &count) != 1 || count == 0U || count > MAX_VALUES) {
        fputs("Invalid list size\n", stderr);
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(double)) {
        fputs("List size is too large\n", stderr);
        return EXIT_FAILURE;
    }

    double *values = malloc(count * sizeof(*values));

    if (values == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < count; ++i) {
        if (scanf("%lf", &values[i]) != 1) {
            fputs("Invalid list value\n", stderr);
            free(values);
            return EXIT_FAILURE;
        }
    }

    double average = 0.0;

    if (!calculate_average(values, count, &average)) {
        fputs("Unable to calculate average\n", stderr);
        free(values);
        return EXIT_FAILURE;
    }

    if (printf("%.17g\n", average) < 0) {
        fputs("Output error\n", stderr);
        free(values);
        return EXIT_FAILURE;
    }

    free(values);
    return EXIT_SUCCESS;
}