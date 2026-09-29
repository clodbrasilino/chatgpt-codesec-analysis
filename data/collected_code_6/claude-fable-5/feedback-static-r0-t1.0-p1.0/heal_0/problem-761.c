#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265358979323846

double arc_length(double radius, double angle_degrees)
{
    return (angle_degrees / 360.0) * 2.0 * PI * radius;
}

int main(void)
{
    double radius;
    double angle;
    double result;

    printf("Enter the radius: ");
    if (scanf("%lf", &radius) != 1) {
        fprintf(stderr, "Error: invalid input for radius.\n");
        return EXIT_FAILURE;
    }

    if (radius < 0.0) {
        fprintf(stderr, "Error: radius must be non-negative.\n");
        return EXIT_FAILURE;
    }

    printf("Enter the angle in degrees: ");
    if (scanf("%lf", &angle) != 1) {
        fprintf(stderr, "Error: invalid input for angle.\n");
        return EXIT_FAILURE;
    }

    if (angle < 0.0 || angle > 360.0) {
        fprintf(stderr, "Error: angle must be between 0 and 360 degrees.\n");
        return EXIT_FAILURE;
    }

    result = arc_length(radius, angle);

    if (isnan(result) || isinf(result)) {
        fprintf(stderr, "Error: computation resulted in an invalid value.\n");
        return EXIT_FAILURE;
    }

    printf("Arc length: %f\n", result);

    return EXIT_SUCCESS;
}