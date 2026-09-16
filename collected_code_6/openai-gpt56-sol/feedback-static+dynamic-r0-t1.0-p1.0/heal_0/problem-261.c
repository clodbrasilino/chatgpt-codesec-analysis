#include <errno.h>
#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double dividend;
    double divisor;
} Tuple;

static int divide_tuples(const Tuple *tuples, size_t count, double *results)
{
    if ((count > 0U) && ((tuples == NULL) || (results == NULL))) {
        return EINVAL;
    }

    for (size_t i = 0U; i < count; ++i) {
        if (!isfinite(tuples[i].dividend) ||
            !isfinite(tuples[i].divisor) ||
            tuples[i].divisor == 0.0) {
            return EDOM;
        }

        results[i] = tuples[i].dividend / tuples[i].divisor;

        if (!isfinite(results[i])) {
            return ERANGE;
        }
    }

    return 0;
}

int main(void)
{
    const Tuple tuples[] = {
        {10.0, 2.0},
        {9.0, 3.0},
        {7.5, 2.5}
    };
    const size_t count = sizeof tuples / sizeof tuples[0];
    double *results = calloc(count, sizeof *results);

    if (results == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    const int status = divide_tuples(tuples, count, results);

    if (status != 0) {
        fprintf(stderr, "Division failed with error code %d\n", status);
        free(results);
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < count; ++i) {
        if (printf("%.17g / %.17g = %.17g\n",
                   tuples[i].dividend,
                   tuples[i].divisor,
                   results[i]) < 0) {
            free(results);
            return EXIT_FAILURE;
        }
    }

    free(results);
    return EXIT_SUCCESS;
}