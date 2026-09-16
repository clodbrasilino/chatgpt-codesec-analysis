#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int polar_to_rectangular(double radius, double angle, double *x, double *y)
{
    if (x == NULL || y == NULL || !isfinite(radius) || !isfinite(angle)) {
        return 0;
    }

    *x = radius * cos(angle);
    *y = radius * sin(angle);

    return isfinite(*x) && isfinite(*y);
}

int main(void)
{
    double radius;
    double angle;
    double x;
    double y;

    errno = 0;

    if (scanf("%lf %lf", &radius, &angle) != 2) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (errno != 0 || !polar_to_rectangular(radius, angle, &x, &y)) {
        fputs("Conversion failed\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("x = %.10g\ny = %.10g\n", x, y) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}