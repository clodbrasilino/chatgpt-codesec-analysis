#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int complex_length(double real, double imaginary, double *result)
{
    if (result == NULL || !isfinite(real) || !isfinite(imaginary)) {
        return -1;
    }

    errno = 0;
    const double length = hypot(real, imaginary);

    if (errno != 0 || !isfinite(length)) {
        return -1;
    }

    *result = length;
    return 0;
}

int main(void)
{
    const double real = 3.0;
    const double imaginary = 4.0;
    double length = 0.0;

    if (complex_length(real, imaginary, &length) != 0) {
        fputs("Failed to calculate the complex number length.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%.17g\n", length) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}