#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double calculate_square_pyramid_surface_area(double base, double height) {
    if (base < 0.0 || height < 0.0) {
        return -1.0;
    }
    double slant_height = sqrt((base / 2.0) * (base / 2.0) + height * height);
    double base_area = base * base;
    double lateral_area = 2.0 * base * slant_height;
    return base_area + lateral_area;
}

int main(int argc, char * const argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <base_length> <height>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr_base;
    char *endptr_height;
    double base = strtod(argv[1], &endptr_base);
    double height = strtod(argv[2], &endptr_height);
    if (endptr_base == argv[1] || *endptr_base != '\0' || endptr_height == argv[2] || *endptr_height != '\0') {
        fprintf(stderr, "Invalid input: Arguments must be valid numbers.\n");
        return EXIT_FAILURE;
    }
    double area = calculate_square_pyramid_surface_area(base, height);
    if (area < 0.0) {
        fprintf(stderr, "Invalid input: Base and height must be non-negative.\n");
        return EXIT_FAILURE;
    }
    printf("%.4f\n", area);
    return EXIT_SUCCESS;
}