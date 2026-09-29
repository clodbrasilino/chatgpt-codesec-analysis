#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double calculate_cylinder_surface_area(double radius) {
    if (radius < 0.0) {
        return -1.0;
    }
    return M_PI * radius * radius;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <radius>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    double radius = strtod(argv[1], &endptr);

    if (endptr == argv[1] || *endptr != '\0') {
        fprintf(stderr, "Invalid radius provided\n");
        return EXIT_FAILURE;
    }

    double area = calculate_cylinder_surface_area(radius);

    if (area < 0.0) {
        fprintf(stderr, "Radius cannot be negative\n");
        return EXIT_FAILURE;
    }

    printf("%.6f\n", area);
    return EXIT_SUCCESS;
}