#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

double babylonian_sqrt(double n, double tolerance) {
    if (n < 0.0) {
        return NAN;
    }
    if (n == 0.0) {
        return 0.0;
    }
    if (isnan(n)) {
        return NAN;
    }
    if (isinf(n)) {
        return INFINITY;
    }

    double x = n;
    if (n > 1.0) {
        x = n / 2.0;
    }

    double prev = 0.0;
    while (fabs(x - prev) > tolerance) {
        prev = x;
        x = (x + n / x) / 2.0;
    }

    return x;
}

int main(int argc, char const * const argv[]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }

    char *endptr;
    double input = strtod(argv[1], &endptr);

    if (*endptr != '\0') {
        return EXIT_FAILURE;
    }

    double result = babylonian_sqrt(input, DBL_EPSILON);

    if (isnan(result)) {
        printf("nan\n");
    } else if (isinf(result)) {
        printf("inf\n");
    } else {
        printf("%.15f\n", result);
    }

    return EXIT_SUCCESS;
}