#include <errno.h>
#include <float.h>
#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static int divide_tuples(const double *numerators,
                         const double *denominators,
                         double *results,
                         size_t count)
{
    if (numerators == NULL || denominators == NULL || results == NULL) {
        return EINVAL;
    }

    for (size_t i = 0U; i < count; ++i) {
        if (!isfinite(numerators[i]) || !isfinite(denominators[i])) {
            return EDOM;
        }

        if (fabs(denominators[i]) < DBL_MIN) {
            return ERANGE;
        }

        results[i] = numerators[i] / denominators[i];

        if (!isfinite(results[i])) {
            return ERANGE;
        }
    }

    return 0;
}

int main(void)
{
    const double numerators[] = {10.0, 20.0, 30.0, 40.0};
    const double denominators[] = {2.0, 4.0, 5.0, 8.0};
    const size_t count = sizeof(numerators) / sizeof(numerators[0]);
    double *results = calloc(count, sizeof(*results));

    if (results == NULL) {
        fputs("Memory allocation failed.\n", stderr);
        return EXIT_FAILURE;
    }

    const int status = divide_tuples(numerators, denominators, results, count);

    if (status != 0) {
        fprintf(stderr, "Division failed with error code %d.\n", status);
        free(results);
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < count; ++i) {
        if (printf("%.17g / %.17g = %.17g\n",
                   numerators[i],
                   denominators[i],
                   results[i]) < 0) {
            fputs("Output failed.\n", stderr);
            free(results);
            return EXIT_FAILURE;
        }
    }

    free(results);
    return EXIT_SUCCESS;
}