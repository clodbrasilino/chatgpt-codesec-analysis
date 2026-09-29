#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

double circle_area(double radius) {
    if (radius < 0) {
        return -1.0;
    }
    return M_PI * radius * radius;
}

int main(int argc, char * const argv[]) {
    double radius;
    double area;
    char *endptr;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <radius>\n", argv[0]);
        return EXIT_FAILURE;
    }

    radius = strtod(argv[1], &endptr);
    if (endptr == argv[1] || *endptr != '\0') {
        fprintf(stderr, "Error: Invalid radius value\n");
        return EXIT_FAILURE;
    }

    area = circle_area(radius);
    if (area < 0) {
        fprintf(stderr, "Error: Radius cannot be negative\n");
        return EXIT_FAILURE;
    }

    printf("%.10f\n", area);
    return EXIT_SUCCESS;
}