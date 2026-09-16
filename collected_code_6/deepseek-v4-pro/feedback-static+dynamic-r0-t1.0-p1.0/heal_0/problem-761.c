#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

double arc_length(double radius, double angle_degrees) {
    if (radius < 0) {
        fprintf(stderr, "Error: radius cannot be negative\n");
        exit(EXIT_FAILURE);
    }
    double angle_radians = angle_degrees * M_PI / 180.0;
    return radius * angle_radians;
}

int main(void) {
    double radius;
    double angle;
    int result;

    printf("Enter radius: ");
    result = scanf("%lf", &radius);
    if (result != 1) {
        fprintf(stderr, "Error: invalid input for radius\n");
        return EXIT_FAILURE;
    }

    printf("Enter angle in degrees: ");
    result = scanf("%lf", &angle);
    if (result != 1) {
        fprintf(stderr, "Error: invalid input for angle\n");
        return EXIT_FAILURE;
    }

    double length = arc_length(radius, angle);
    printf("Arc length: %.6f\n", length);

    return EXIT_SUCCESS;
}