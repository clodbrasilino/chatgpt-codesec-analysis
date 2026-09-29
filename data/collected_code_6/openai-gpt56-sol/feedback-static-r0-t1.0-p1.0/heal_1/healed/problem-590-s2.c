#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int polar_to_rectangular(double radius, double angle, double *x, double *y)
{
    if (x == NULL || y == NULL || !isfinite(radius) || !isfinite(angle)) {
        return -1;
    }

    *x = radius * cos(angle);
    *y = radius * sin(angle);

    return (isfinite(*x) && isfinite(*y)) ? 0 : -1;
}

int main(int argc, char *const argv[])
{
    char *end = NULL;
    double radius;
    double angle;
    double x;
    double y;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <radius> <angle_in_radians>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    radius = strtod(argv[1], &end);
    if (errno != 0 || end == argv[1] || *end != '\0' || !isfinite(radius)) {
        fputs("Invalid radius\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    angle = strtod(argv[2], &end);
    if (errno != 0 || end == argv[2] || *end != '\0' || !isfinite(angle)) {
        fputs("Invalid angle\n", stderr);
        return EXIT_FAILURE;
    }

    if (polar_to_rectangular(radius, angle, &x, &y) != 0) {
        fputs("Coordinate conversion failed\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("x = %.17g\ny = %.17g\n", x, y) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}