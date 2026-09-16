#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

double cone_volume(double radius, double height)
{
    return (M_PI * radius * radius * height) / 3.0;
}

int main(void)
{
    double radius;
    double height;

    printf("Enter the radius of the cone: ");
    if (scanf("%lf", &radius) != 1) {
        fprintf(stderr, "Error: invalid input for radius.\n");
        return EXIT_FAILURE;
    }

    if (radius < 0.0 || !isfinite(radius)) {
        fprintf(stderr, "Error: radius must be a non-negative finite number.\n");
        return EXIT_FAILURE;
    }

    printf("Enter the height of the cone: ");
    if (scanf("%lf", &height) != 1) {
        fprintf(stderr, "Error: invalid input for height.\n");
        return EXIT_FAILURE;
    }

    if (height < 0.0 || !isfinite(height)) {
        fprintf(stderr, "Error: height must be a non-negative finite number.\n");
        return EXIT_FAILURE;
    }

    double volume = cone_volume(radius, height);

    if (!isfinite(volume)) {
        fprintf(stderr, "Error: computation overflowed.\n");
        return EXIT_FAILURE;
    }

    printf("Volume of the cone: %f\n", volume);

    return EXIT_SUCCESS;
}