#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double calculate_lateral_surface_area(double radius, double height) {
    if (radius < 0.0 || height < 0.0) {
        return -1.0;
    }
    return 2.0 * M_PI * radius * height;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <radius> <height>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr_r;
    char *endptr_h;
    double radius = strtod(argv[1], &endptr_r);
    double height = strtod(argv[2], &endptr_h);

    if (endptr_r == argv[1] || *endptr_r != '\0' || endptr_h == argv[2] || *endptr_h != '\0') {
        fprintf(stderr, "Invalid input: radius and height must be valid numbers\n");
        return EXIT_FAILURE;
    }

    double area = calculate_lateral_surface_area(radius, height);

    if (area < 0.0) {
        fprintf(stderr, "Invalid input: radius and height must be non-negative\n");
        return EXIT_FAILURE;
    }

    printf("%.6f\n", area);
    return EXIT_SUCCESS;
}