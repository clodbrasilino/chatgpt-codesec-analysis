#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int babylonian_sqrt(double value, double *result)
{
    double estimate;
    int iteration;
    const int max_iterations = 1000;

    if (result == NULL || !isfinite(value) || value < 0.0) {
        return -1;
    }

    if (value == 0.0) {
        *result = 0.0;
        return 0;
    }

    estimate = value >= 1.0 ? value : 1.0;

    for (iteration = 0; iteration < max_iterations; ++iteration) {
        const double previous = estimate;

        estimate = 0.5 * (previous + value / previous);

        if (!isfinite(estimate)) {
            return -1;
        }

        if (fabs(estimate - previous) <= DBL_EPSILON * estimate) {
            *result = estimate;
            return 0;
        }
    }

    return -1;
}

int main(int argc, const char *const argv[])
{
    char *end = NULL;
    double value;
    double result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <non-negative number>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtod(argv[1], &end);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        !isfinite(value) || value < 0.0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (babylonian_sqrt(value, &result) != 0) {
        fprintf(stderr, "Square root computation failed\n");
        return EXIT_FAILURE;
    }

    if (printf("%.17g\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}