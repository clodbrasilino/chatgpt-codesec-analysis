#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double calculate_lateral_surface_area(double radius, double height) {
    if (radius < 0.0 || height < 0.0) {
        return -1.0;
    }
    return 2.0 * M_PI * radius * height;
}

int main(int argc, char * const * const argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <radius> <height>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr_r;
    char *endptr_h;
    double radius = strtod(argv[1], &endptr_r);
    double height = strtod(argv[2], &endptr_h);

    if (*endptr_r != '\0' || *endptr_h != '\0' || radius < 0.0 || height < 0.0) {
        fprintf(stderr, "Invalid input. Radius and height must be non-negative numbers.\n");
        return EXIT_FAILURE;
    }

    double area = calculate_lateral_surface_area(radius, height);
    printf("%.6f\n", area);

    return EXIT_SUCCESS;
}