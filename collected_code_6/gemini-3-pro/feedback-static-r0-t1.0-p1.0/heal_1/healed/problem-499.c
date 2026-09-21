#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>

double calculate_diameter(double radius) {
    if (radius < 0.0) {
        return -1.0;
    }
    return 2.0 * radius;
}

int main(void) {
    double radius;
    double diameter;
    char *buffer = NULL;
    size_t bufsize = 0;

    if (getline(&buffer, &bufsize, stdin) == -1) {
        free(buffer);
        return EXIT_FAILURE;
    }

    char *endptr;
    radius = strtod(buffer, &endptr);

    if (endptr == buffer || (*endptr != '\n' && *endptr != '\0')) {
        free(buffer);
        return EXIT_FAILURE;
    }

    free(buffer);

    diameter = calculate_diameter(radius);

    if (diameter < 0.0) {
        return EXIT_FAILURE;
    }

    printf("%f\n", diameter);

    return EXIT_SUCCESS;
}