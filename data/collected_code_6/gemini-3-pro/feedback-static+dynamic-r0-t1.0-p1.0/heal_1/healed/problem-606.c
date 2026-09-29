#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

double degrees_to_radians(double degrees);

double degrees_to_radians(double degrees) {
    return degrees * (M_PI / 180.0);
}

int main(void) {
    char *buffer = NULL;
    size_t bufsize = 0;
    double degrees;
    double radians;
    char *endptr;

    if (getline(&buffer, &bufsize, stdin) == -1) {
        free(buffer);
        return EXIT_FAILURE;
    }

    degrees = strtod(buffer, &endptr);

    if (endptr == buffer || (*endptr != '\n' && *endptr != '\0' && *endptr != '\r')) {
        free(buffer);
        return EXIT_FAILURE;
    }

    radians = degrees_to_radians(degrees);

    if (printf("%f\n", radians) < 0) {
        free(buffer);
        return EXIT_FAILURE;
    }

    free(buffer);
    return EXIT_SUCCESS;
}