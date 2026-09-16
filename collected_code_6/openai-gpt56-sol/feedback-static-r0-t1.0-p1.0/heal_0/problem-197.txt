#include <errno.h>
#include <math.h>
#include <stddef.h>
#include <stdio.h>

typedef struct {
    double first;
    double second;
} Tuple;

static int exponentiate_tuples(const Tuple *base, const Tuple *exponent, Tuple *result)
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
    Tuple base = {2.0, 3.0};
    Tuple exponent = {4.0, 2.0};
    Tuple result = {0.0, 0.0};

    if (exponentiate_tuples(&base, &exponent, &result) != 0) {
        fputs("Exponentiation failed\n", stderr);
        return 1;
    }

    if (printf("(%.17g, %.17g)\n", result.first, result.second) < 0) {
        return 1;
    }

    return 0;
}