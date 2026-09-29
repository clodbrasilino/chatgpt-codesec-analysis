#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double calculate_sphere_surface_area(double radius) {
    return 4.0 * M_PI * radius * radius;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <radius>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    double radius = strtod(argv[1], &endptr);

    if (endptr == argv[1] || *endptr != '\0') {
        fprintf(stderr, "Invalid input: Not a valid number.\n");
        return EXIT_FAILURE;
    }

    if (radius < 0.0) {
        fprintf(stderr, "Invalid input: Radius cannot be negative.\n");
        return EXIT_FAILURE;
    }

    double surface_area = calculate_sphere_surface_area(radius);

    if (fprintf(stdout, "%.15g\n", surface_area) < 0) {
        fprintf(stderr, "Failed to write output.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}