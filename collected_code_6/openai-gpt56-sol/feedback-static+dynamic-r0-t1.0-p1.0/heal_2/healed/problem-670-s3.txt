#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static bool has_decreasing_trend(const double values[], size_t count)
{
    if (values == NULL || count < 2U) {
        return false;
    }

    for (size_t i = 1U; i < count; ++i) {
        if (!(values[i] < values[i - 1U])) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    size_t count;

    if (scanf("%zu", &count) != 1 ||
        count < 2U ||
        count > SIZE_MAX / sizeof(double)) {
        fprintf(stderr, "Invalid sequence length.\n");
        return EXIT_FAILURE;
    }

    double *values = malloc(count * sizeof(*values));
    if (values == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < count; ++i) {
        if (scanf("%lf", &values[i]) != 1) {
            fprintf(stderr, "Invalid numeric input.\n");
            free(values);
            return EXIT_FAILURE;
        }
    }

    printf("%s\n", has_decreasing_trend(values, count) ? "true" : "false");

    free(values);
    return EXIT_SUCCESS;
}