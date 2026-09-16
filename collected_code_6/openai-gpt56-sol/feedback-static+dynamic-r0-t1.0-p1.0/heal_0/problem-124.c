#include <complex.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int complex_angle(double complex value, double *angle)
{
    if (angle == NULL || !isfinite(creal(value)) || !isfinite(cimag(value))) {
        return -1;
    }

    errno = 0;
    double result = carg(value);

    if (errno != 0 || !isfinite(result)) {
        return -1;
    }

    *angle = result;
    return 0;
}

int main(void)
{
    const double complex value = 3.0 + 4.0 * I;
    double angle = 0.0;

    if (complex_angle(value, &angle) != 0) {
        fputs("Failed to calculate the angle.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%.17g\n", angle) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}