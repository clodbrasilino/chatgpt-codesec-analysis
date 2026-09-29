#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int cylinder_perimeter(double radius, double height, double *result)
{
    const double pi = acos(-1.0);
    double value;

    if (result == NULL ||
        !isfinite(radius) ||
        !isfinite(height) ||
        radius < 0.0 ||
        height < 0.0) {
        return -1;
    }

    value = 2.0 * (2.0 * pi * radius + height);

    if (!isfinite(value)) {
        return -1;
    }

    *result = value;
    return 0;
}

int main(void)
{
    double radius;
    double height;
    double perimeter;
    int ch;

    if (scanf("%lf %lf", &radius, &height) != 2) {
        return EXIT_FAILURE;
    }

    do {
        ch = getchar();
    } while (ch == ' ' || ch == '\t' || ch == '\n' ||
             ch == '\r' || ch == '\f' || ch == '\v');

    if (ch != EOF) {
        return EXIT_FAILURE;
    }

    if (errno == ERANGE ||
        !isfinite(radius) ||
        !isfinite(height) ||
        cylinder_perimeter(radius, height, &perimeter) != 0) {
        return EXIT_FAILURE;
    }

    if (printf("%.10g\n", perimeter) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}