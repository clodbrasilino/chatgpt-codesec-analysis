#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int geometric_term(double first, double ratio, unsigned long long term,
                          double *result)
{
    if (result == NULL || term == 0U || !isfinite(first) || !isfinite(ratio)) {
        return 0;
    }

    errno = 0;
    *result = first * pow(ratio, (double)(term - 1U));

    if (errno != 0 || !isfinite(*result)) {
        return 0;
    }

    return 1;
}

int main(void)
{
    double first = 0.0;
    double ratio = 0.0;
    double result = 0.0;
    unsigned long long term = 0U;

    if (scanf("%lf %lf %llu", &first, &ratio, &term) != 3) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!geometric_term(first, ratio, term, &result)) {
        fputs("Unable to calculate the requested term\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%.17g\n", result);
    return EXIT_SUCCESS;
}