#include <errno.h>
#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double first;
    double second;
} Tuple;

static int exponentiate_tuples(const Tuple *base, const Tuple *exponent,
                               Tuple *result)
{
    if (base == NULL || exponent == NULL || result == NULL) {
        return -1;
    }

    errno = 0;
    result->first = pow(base->first, exponent->first);
    if (errno != 0 || !isfinite(result->first)) {
        return -1;
    }

    errno = 0;
    result->second = pow(base->second, exponent->second);
    if (errno != 0 || !isfinite(result->second)) {
        return -1;
    }

    return 0;
}

int main(void)
{
    Tuple base;
    Tuple exponent;
    Tuple result;

    if (scanf("%lf %lf", &base.first, &base.second) != 2) {
        fputs("Invalid base tuple\n", stderr);
        return EXIT_FAILURE;
    }

    if (scanf("%lf %lf", &exponent.first, &exponent.second) != 2) {
        fputs("Invalid exponent tuple\n", stderr);
        return EXIT_FAILURE;
    }

    if (exponentiate_tuples(&base, &exponent, &result) != 0) {
        fputs("Exponentiation failed\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("(%.17g, %.17g)\n", result.first, result.second) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}