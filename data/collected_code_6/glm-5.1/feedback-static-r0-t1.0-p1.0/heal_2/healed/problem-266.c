#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <string.h>

double calculate_lateral_surface_area(double side) {
    if (side < 0.0) {
        errno = EDOM;
        return -1.0;
    }
    if (side > (double)(ULLONG_MAX / 4.0)) {
        errno = ERANGE;
        return -1.0;
    }
    return 4.0 * side * side;
}

int main(int argc, const char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <side_length>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    errno = 0;
    double side = strtod(argv[1], &endptr);

    if (errno == ERANGE || endptr == argv[1] || *endptr != '\0') {
        fprintf(stderr, "Invalid input: Not a valid number\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    double area = calculate_lateral_surface_area(side);

    if (errno != 0) {
        fprintf(stderr, "Error calculating area: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    printf("%.6f\n", area);

    return EXIT_SUCCESS;
}