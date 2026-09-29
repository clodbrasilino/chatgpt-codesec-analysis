#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int geometric_term(double first, double ratio, unsigned int term, double *result)
{
    double value;

    if (result == NULL || term == 0U || !isfinite(first) || !isfinite(ratio)) {
        return -1;
    }

    errno = 0;
    value = first * pow(ratio, (double)(term - 1U));

    if (errno != 0 || !isfinite(value)) {
        return -1;
    }

    *result = value;
    return 0;
}

int main(void)
{
    double first;
    double ratio;
    double result;
    unsigned int term;

    if (scanf("%lf %lf %u", &first, &ratio, &term) != 3) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (geometric_term(first, ratio, term, &result) != 0) {
        fputs("Unable to calculate the term\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%.17g\n", result);
    return EXIT_SUCCESS;
}