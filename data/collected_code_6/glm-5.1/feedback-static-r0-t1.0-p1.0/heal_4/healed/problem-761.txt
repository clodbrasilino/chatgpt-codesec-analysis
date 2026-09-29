#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double calculate_arc_length(double radius, double angle_degrees) {
    if (radius < 0.0) {
        fprintf(stderr, "Invalid radius\n");
        exit(EXIT_FAILURE);
    }
    double angle_radians = angle_degrees * (M_PI / 180.0);
    return fabs(radius * angle_radians);
}

int main(int argc, char * const * const argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <radius> <angle_in_degrees>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    char *endptr_radius;
    double radius = strtod(argv[1], &endptr_radius);
    if (*endptr_radius != '\0') {
        fprintf(stderr, "Invalid radius format\n");
        return EXIT_FAILURE;
    }

    char *endptr_angle;
    double angle = strtod(argv[2], &endptr_angle);
    if (*endptr_angle != '\0') {
        fprintf(stderr, "Invalid angle format\n");
        return EXIT_FAILURE;
    }

    double arc_length = calculate_arc_length(radius, angle);
    printf("%f\n", arc_length);

    return EXIT_SUCCESS;
}