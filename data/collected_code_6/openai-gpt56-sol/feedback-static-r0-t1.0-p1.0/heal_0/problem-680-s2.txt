#include <stdio.h>
#include <stdlib.h>

static int has_increasing_trend(const double values[], size_t count)
{
    size_t i;

    if (values == NULL || count < 2U) {
        return 0;
    }

    for (i = 1U; i < count; ++i) {
        if (values[i] <= values[i - 1U]) {
            return 0;
        }
    }

    return 1;
}

int main(void)
{
    size_t count;
    size_t i;
    double *values;

    if (printf("Enter the number of values: ") < 0) {
        return EXIT_FAILURE;
    }

    if (scanf("%zu", &count) != 1 || count < 2U ||
        count > SIZE_MAX / sizeof(*values)) {
        fprintf(stderr, "Invalid number of values.\n");
        return EXIT_FAILURE;
    }

    values = malloc(count * sizeof(*values));
    if (values == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    if (printf("Enter %zu values: ", count) < 0) {
        free(values);
        return EXIT_FAILURE;
    }

    for (i = 0U; i < count; ++i) {
        if (scanf("%lf", &values[i]) != 1) {
            fprintf(stderr, "Invalid input.\n");
            free(values);
            return EXIT_FAILURE;
        }
    }

    if (has_increasing_trend(values, count) != 0) {
        if (printf("The sequence has an increasing trend.\n") < 0) {
            free(values);
            return EXIT_FAILURE;
        }
    } else {
        if (printf("The sequence does not have an increasing trend.\n") < 0) {
            free(values);
            return EXIT_FAILURE;
        }
    }

    free(values);
    return EXIT_SUCCESS;
}