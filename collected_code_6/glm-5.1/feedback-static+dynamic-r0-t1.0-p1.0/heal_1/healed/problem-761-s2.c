#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double calculate_arc_length(double radius, double angle_degrees) {
    if (radius < 0.0) {
        return -1.0;
    }
    if (angle_degrees < 0.0) {
        return -1.0;
    }
    double angle_radians = angle_degrees * (M_PI / 180.0);
    return radius * angle_radians;
}

int main(int argc, char * const argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <radius> <angle_degrees>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr_radius;
    char *endptr_angle;

    double radius = strtod(argv[1], &endptr_radius);
    double angle = strtod(argv[2], &endptr_angle);

    if (*endptr_radius != '\0' || *endptr_angle != '\0') {
        fprintf(stderr, "Invalid input: arguments must be numeric.\n");
        return EXIT_FAILURE;
    }

    double arc_length = calculate_arc_length(radius, angle);

    if (arc_length < 0.0) {
        fprintf(stderr, "Invalid input: radius and angle must be non-negative.\n");
        return EXIT_FAILURE;
    }

    printf("%f\n", arc_length);

    return EXIT_SUCCESS;
}