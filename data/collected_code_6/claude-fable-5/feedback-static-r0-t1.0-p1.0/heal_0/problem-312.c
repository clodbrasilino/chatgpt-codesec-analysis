#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double cone_volume(double radius, double height)
{
    return (M_PI * radius * radius * height) / 3.0;
}

int main(void)
{
    double radius;
    double height;
    double volume;

    printf("Enter the radius of the cone: ");
    if (scanf("%lf", &radius) != 1) {
        fprintf(stderr, "Error: invalid input for radius.\n");
        return EXIT_FAILURE;
    }

    printf("Enter the height of the cone: ");
    if (scanf("%lf", &height) != 1) {
        fprintf(stderr, "Error: invalid input for height.\n");
        return EXIT_FAILURE;
    }

    if (radius < 0.0 || height < 0.0) {
        fprintf(stderr, "Error: radius and height must be non-negative.\n");
        return EXIT_FAILURE;
    }

    if (!isfinite(radius) || !isfinite(height)) {
        fprintf(stderr, "Error: radius and height must be finite values.\n");
        return EXIT_FAILURE;
    }

    volume = cone_volume(radius, height);

    if (!isfinite(volume)) {
        fprintf(stderr, "Error: result overflowed.\n");
        return EXIT_FAILURE;
    }

    printf("The volume of the cone is: %f\n", volume);

    return EXIT_SUCCESS;
}