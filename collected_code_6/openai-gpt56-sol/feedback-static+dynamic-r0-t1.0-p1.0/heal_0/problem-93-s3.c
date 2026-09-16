#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int calculate_power(double a, double b, double *result)
{
    if (result == NULL || !isfinite(a) || !isfinite(b)) {
        return -1;
    }

    errno = 0;
    *result = pow(a, b);

    if (errno != 0 || !isfinite(*result)) {
        return -1;
    }

    return 0;
}

int main(void)
{
    double a;
    double b;
    double result;

    if (scanf("%lf %lf", &a, &b) != 2) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (calculate_power(a, b, &result) != 0) {
        fputs("Unable to calculate power\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%.17g\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}