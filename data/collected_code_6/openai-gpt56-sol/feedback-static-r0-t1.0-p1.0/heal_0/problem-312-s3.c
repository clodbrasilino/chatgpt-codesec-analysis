#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static int cone_volume(double radius, double height, double *volume)
{
    const double pi = 3.14159265358979323846;

    if (volume == NULL || !isfinite(radius) || !isfinite(height) ||
        radius < 0.0 || height < 0.0) {
        return 0;
    }

    *volume = (pi * radius * radius * height) / 3.0;

    return isfinite(*volume);
}

int main(void)
{
    double radius;
    double height;
    double volume;

    if (printf("Enter radius and height: ") < 0) {
        return EXIT_FAILURE;
    }

    if (scanf("%lf %lf", &radius, &height) != 2) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    if (!cone_volume(radius, height, &volume)) {
        fprintf(stderr, "Radius and height must be finite, nonnegative values.\n");
        return EXIT_FAILURE;
    }

    if (printf("Volume: %.6f\n", volume) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}