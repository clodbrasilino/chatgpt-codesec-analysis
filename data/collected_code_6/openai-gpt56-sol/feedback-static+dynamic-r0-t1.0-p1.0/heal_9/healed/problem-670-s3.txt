#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool has_decreasing_trend(const double values[], size_t count)
{
    if (values == NULL || count < 2U) {
        return false;
    }

    bool has_decrease = false;

    for (size_t i = 0U; i < count; ++i) {
        if (!isfinite(values[i])) {
            return false;
        }

        if (i > 0U) {
            if (values[i] > values[i - 1U]) {
                return false;
            }
            if (values[i] < values[i - 1U]) {
                has_decrease = true;
            }
        }
    }

    return has_decrease;
}

int main(void)
{
    size_t count;

    if (scanf("%zu", &count) != 1 ||
        count < 2U ||
        count > SIZE_MAX / sizeof(double)) {
        return EXIT_FAILURE;
    }

    double *values = malloc(count * sizeof(*values));
    if (values == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < count; ++i) {
        if (scanf("%lf", &values[i]) != 1 || !isfinite(values[i])) {
            free(values);
            return EXIT_FAILURE;
        }
    }

    puts(has_decreasing_trend(values, count) ? "True" : "False");

    free(values);
    return EXIT_SUCCESS;
}