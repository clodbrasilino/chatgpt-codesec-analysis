#include <stdio.h>
#include <stdlib.h>

double calculate_diameter(double radius) {
    if (radius < 0.0) {
        return -1.0;
    }
    return 2.0 * radius;
}

int main(int argc, char *argv[]) {
    double radius = 0.0;
    double diameter = 0.0;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <radius>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (sscanf(argv[1], "%lf", &radius) != 1) {
        fprintf(stderr, "Invalid input: Not a valid number\n");
        return EXIT_FAILURE;
    }

    diameter = calculate_diameter(radius);

    if (diameter < 0.0) {
        fprintf(stderr, "Invalid input: Radius cannot be negative\n");
        return EXIT_FAILURE;
    }

    printf("%.6f\n", diameter);

    return EXIT_SUCCESS;
}