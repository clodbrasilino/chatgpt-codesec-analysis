#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int babylonian_sqrt(double value, double *result)
{
    const double tolerance = 1e-12;
    const size_t max_iterations = 1000;
    double estimate;
    size_t iteration;

    if (result == NULL || !isfinite(value) || value < 0.0) {
        return -1;
    }

    if (value == 0.0) {
        *result = 0.0;
        return 0;
    }

    estimate = value >= 1.0 ? value : 1.0;

    for (iteration = 0; iteration < max_iterations; ++iteration) {
        double next = 0.5 * (estimate + value / estimate);

        if (!isfinite(next)) {
            return -1;
        }

        if (fabs(next - estimate) <= tolerance * fmax(1.0, fabs(next))) {
            *result = next;
            return 0;
        }

        estimate = next;
    }

    return -1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
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