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

    printf("Enter the radius and height of the cone: ");

    if (scanf("%lf %lf", &radius, &height) != 2) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    if (!cone_volume(radius, height, &volume)) {
        fprintf(stderr, "Unable to calculate the volume.\n");
        return EXIT_FAILURE;
    }

    printf("Volume of the cone: %.6f\n", volume);
    return EXIT_SUCCESS;
}