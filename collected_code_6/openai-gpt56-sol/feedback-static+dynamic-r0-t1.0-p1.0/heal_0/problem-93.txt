#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int calculate_power(double base, double exponent, double *result)
{
    if (result == NULL || !isfinite(base) || !isfinite(exponent)) {
        return -1;
    }

    errno = 0;
    *result = pow(base, exponent);

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

    printf("Enter a and b: ");

    if (scanf("%lf %lf", &a, &b) != 2) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (calculate_power(a, b, &result) != 0) {
        fputs("Unable to calculate the power\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%.17g\n", result);
    return EXIT_SUCCESS;
}