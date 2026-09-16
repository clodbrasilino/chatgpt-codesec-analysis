#include <errno.h>
#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static int nth_power_elements(const double *input, double *output,
                              size_t count, int exponent)
{
    if ((count > 0U) && ((input == NULL) || (output == NULL))) {
        return -1;
    }

    for (size_t i = 0U; i < count; ++i) {
        errno = 0;
        output[i] = pow(input[i], exponent);

        if ((errno != 0) || !isfinite(output[i])) {
            return -1;
        }
    }

    return 0;
}

int main(void)
{
    const double values[] = {2.0, 3.0, 4.0, 5.0};
    const size_t count = sizeof(values) / sizeof(values[0]);
    const int exponent = 3;
    double *results = calloc(count, sizeof(*results));

    if (results == NULL) {
        fputs("Memory allocation failed.\n", stderr);
        return EXIT_FAILURE;
    }

    if (nth_power_elements(values, results, count, exponent) != 0) {
        fputs("Power calculation failed.\n", stderr);
        free(results);
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < count; ++i) {
        if (printf("%.2f%s", results[i], (i + 1U < count) ? " " : "\n") < 0) {
            free(results);
            return EXIT_FAILURE;
        }
    }

    free(results);
    return EXIT_SUCCESS;
}