#include <stdio.h>
#include <stdlib.h>

double lateral_surface_area_cuboid(double length, double width, double height) {
    if (length <= 0.0 || width <= 0.0 || height <= 0.0) {
        return -1.0;
    }
    return 2.0 * (length + width) * height;
}

int main(int argc, char const * const * argv) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <length> <width> <height>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    double length = strtod(argv[1], &endptr);
    if (*endptr != '\0' || length <= 0.0) {
        fprintf(stderr, "Invalid or non-positive value for length.\n");
        return EXIT_FAILURE;
    }

    double width = strtod(argv[2], &endptr);
    if (*endptr != '\0' || width <= 0.0) {
        fprintf(stderr, "Invalid or non-positive value for width.\n");
        return EXIT_FAILURE;
    }

    double height = strtod(argv[3], &endptr);
    if (*endptr != '\0' || height <= 0.0) {
        fprintf(stderr, "Invalid or non-positive value for height.\n");
        return EXIT_FAILURE;
    }

    double area = lateral_surface_area_cuboid(length, width, height);

    printf("%.2f\n", area);

    return EXIT_SUCCESS;
}