#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>

double calculate_circle_diameter(double radius) {
    if (radius < 0.0) {
        errno = EDOM;
        return NAN;
    }
    return 2.0 * radius;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    double radius = 0.0;
    double diameter = 0.0;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <radius>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    errno = 0;
    radius = strtod(argv[1], &endptr);

    if (errno == ERANGE) {
        perror("strtod");
        return EXIT_FAILURE;
    }

    if (endptr == argv[1] || *endptr != '\0') {
        fprintf(stderr, "Invalid input: not a valid number\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    diameter = calculate_circle_diameter(radius);

    if (errno == EDOM) {
        fprintf(stderr, "Invalid input: radius cannot be negative\n");
        return EXIT_FAILURE;
    }

    printf("%.6f\n", diameter);

    return EXIT_SUCCESS;
}