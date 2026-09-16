#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int complex_length(double real, double imaginary, double *length)
{
    if (length == NULL || !isfinite(real) || !isfinite(imaginary)) {
        return -1;
    }

    errno = 0;
    *length = hypot(real, imaginary);

    if (errno != 0 || !isfinite(*length)) {
        return -1;
    }

    return 0;
}

int main(void)
{
    double real;
    double imaginary;
    double length;

    if (scanf("%lf %lf", &real, &imaginary) != 2) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (complex_length(real, imaginary, &length) != 0) {
        fputs("Unable to calculate the complex number length\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%.17g\n", length);
    return EXIT_SUCCESS;
}