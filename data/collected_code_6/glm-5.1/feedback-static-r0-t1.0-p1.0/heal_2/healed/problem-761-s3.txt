#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double calculate_arc_length(double radius, double angle_degrees) {
    if (radius < 0.0) {
        return NAN;
    }
    double angle_radians = angle_degrees * (M_PI / 180.0);
    return radius * angle_radians;
}

int main(int argc, char * const * argv) {
    double radius = 0.0;
    double angle = 0.0;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <radius> <angle_in_degrees>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr_radius = NULL;
    radius = strtod(argv[1], &endptr_radius);
    if (endptr_radius == argv[1] || *endptr_radius != '\0') {
        fprintf(stderr, "Error: Invalid radius format\n");
        return EXIT_FAILURE;
    }

    char *endptr_angle = NULL;
    angle = strtod(argv[2], &endptr_angle);
    if (endptr_angle == argv[2] || *endptr_angle != '\0') {
        fprintf(stderr, "Error: Invalid angle format\n");
        return EXIT_FAILURE;
    }

    double arc_length = calculate_arc_length(radius, angle);
    if (isnan(arc_length)) {
        fprintf(stderr, "Error: Radius cannot be negative\n");
        return EXIT_FAILURE;
    }

    printf("%f\n", arc_length);

    return EXIT_SUCCESS;
}