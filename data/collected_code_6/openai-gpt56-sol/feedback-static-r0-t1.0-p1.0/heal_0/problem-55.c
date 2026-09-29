#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int geometric_term(double first, double ratio, long long term, double *result)
{
    if (result == NULL || term < 1 || !isfinite(first) || !isfinite(ratio)) {
        return 0;
    }

    errno = 0;
    double value = first * pow(ratio, (double)(term - 1));

    if (errno != 0 || !isfinite(value)) {
        return 0;
    }

    *result = value;
    return 1;
}

int main(void)
{
    double first;
    double ratio;
    double result;
    long long term;

    if (scanf("%lf %lf %lld", &first, &ratio, &term) != 3) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!geometric_term(first, ratio, term, &result)) {
        fputs("Unable to calculate the term\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%.17g\n", result);
    return EXIT_SUCCESS;
}