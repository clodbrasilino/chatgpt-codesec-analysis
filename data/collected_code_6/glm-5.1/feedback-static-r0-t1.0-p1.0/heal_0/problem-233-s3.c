#include <stdio.h>
#include <stdlib.h>

double calculate_lateral_surface_area(double radius, double height) {
    if (radius < 0.0 || height < 0.0) {
        return -1.0;
    }
    return 2.0 * 3.14159265358979323846 * radius * height;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <radius> <height>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr_radius;
    char *endptr_height;
    
    double radius = strtod(argv[1], &endptr_radius);
    double height = strtod(argv[2], &endptr_height);

    if (*endptr_radius != '\0' || *endptr_height != '\0') {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    double area = calculate_lateral_surface_area(radius, height);
    if (area < 0.0) {
        fprintf(stderr, "Invalid dimensions.\n");
        return EXIT_FAILURE;
    }

    printf("%.6f\n", area);
    return EXIT_SUCCESS;
}