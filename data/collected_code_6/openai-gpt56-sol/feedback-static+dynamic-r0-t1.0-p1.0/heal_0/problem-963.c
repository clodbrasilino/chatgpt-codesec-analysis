#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int calculate_discriminant(double a, double b, double c, double *result)
{
    if (result == NULL || !isfinite(a) || !isfinite(b) || !isfinite(c)) {
        return 0;
    }

    errno = 0;
    const double discriminant = fma(-4.0 * a, c, b * b);

    if (errno != 0 || !isfinite(discriminant)) {
        return 0;
    }

    *result = discriminant;
    return 1;
}

int main(void)
{
    double a = 0.0;
    double b = 0.0;
    double c = 0.0;
    double discriminant = 0.0;

    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!calculate_discriminant(a, b, c, &discriminant)) {
        fputs("Unable to calculate discriminant\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%.17g\n", discriminant) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}