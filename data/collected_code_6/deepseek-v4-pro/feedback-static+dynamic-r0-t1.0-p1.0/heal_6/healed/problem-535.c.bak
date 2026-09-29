#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

double cylinder_surface_area(double radius, double height) {
    if (radius < 0 || height < 0) {
        return -1.0;
    }
    return 2.0 * M_PI * radius * radius + 2.0 * M_PI * radius * height;
}

int main(int argc, char *argv[]) {
    double radius;
    double height;
    double area;
    char *endptr;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <radius> <height>\n", argv[0]);
        return EXIT_FAILURE;
    }

    radius = strtod(argv[1], &endptr);
    if (endptr == argv[1] || *endptr != '\0') {
        fprintf(stderr, "Error: Invalid radius value\n");
        return EXIT_FAILURE;
    }

    height = strtod(argv[2], &endptr);
    if (endptr == argv[2] || *endptr != '\0') {
        fprintf(stderr, "Error: Invalid height value\n");
        return EXIT_FAILURE;
    }

    area = cylinder_surface_area(radius, height);
    if (area < 0) {
        fprintf(stderr, "Error: Radius and height cannot be negative\n");
        return EXIT_FAILURE;
    }

    printf("%.10f\n", area);
    return EXIT_SUCCESS;
}