#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double cylinder_surface_area(double radius) {
    if (radius <= 0.0) {
        return 0.0;
    }
    return M_PI * radius * radius;
}

int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <radius>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    double radius = strtod(argv[1], &endptr);

    if (endptr == argv[1] || *endptr != '\0') {
        fprintf(stderr, "Invalid input: not a valid number\n");
        return EXIT_FAILURE;
    }

    if (radius < 0.0) {
        fprintf(stderr, "Invalid input: radius cannot be negative\n");
        return EXIT_FAILURE;
    }

    double area = cylinder_surface_area(radius);
    printf("%.6f\n", area);

    return EXIT_SUCCESS;
}