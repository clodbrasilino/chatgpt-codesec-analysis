#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double calculate_cylinder_volume(double radius, double height) {
    if (radius < 0.0 || height < 0.0) {
        return -1.0;
    }
    return M_PI * radius * radius * height;
}

int main(int argc, char *argv[]) {
    double radius, height, volume;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <radius> <height>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr_radius;
    char *endptr_height;

    radius = strtod(argv[1], &endptr_radius);
    height = strtod(argv[2], &endptr_height);

    if (endptr_radius == argv[1] || *endptr_radius != '\0' || endptr_height == argv[2] || *endptr_height != '\0') {
        fprintf(stderr, "Error: Invalid numeric input\n");
        return EXIT_FAILURE;
    }

    volume = calculate_cylinder_volume(radius, height);

    if (volume < 0.0) {
        fprintf(stderr, "Error: Dimensions must be non-negative\n");
        return EXIT_FAILURE;
    }

    printf("%.6f\n", volume);

    return EXIT_SUCCESS;
}