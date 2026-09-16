#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int polar_to_rectangular(double radius, double angle_radians,
                                double *x, double *y)
{
    if (x == NULL || y == NULL || !isfinite(radius) ||
        !isfinite(angle_radians) || radius < 0.0) {
        return -1;
    }

    errno = 0;
    const double cosine = cos(angle_radians);
    const double sine = sin(angle_radians);

    if (errno != 0 || !isfinite(cosine) || !isfinite(sine)) {
        return -1;
    }

    const double result_x = radius * cosine;
    const double result_y = radius * sine;

    if (!isfinite(result_x) || !isfinite(result_y)) {
        return -1;
    }

    *x = result_x;
    *y = result_y;
    return 0;
}

int main(void)
{
    double radius = 0.0;
    double angle_radians = 0.0;
    double x = 0.0;
    double y = 0.0;

    if (printf("Enter radius and angle in radians: ") < 0) {
        return EXIT_FAILURE;
    }

    if (scanf("%lf %lf", &radius, &angle_radians) != 2) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    if (polar_to_rectangular(radius, angle_radians, &x, &y) != 0) {
        fprintf(stderr, "Unable to convert the coordinates.\n");
        return EXIT_FAILURE;
    }

    if (printf("x = %.10g\ny = %.10g\n", x, y) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}