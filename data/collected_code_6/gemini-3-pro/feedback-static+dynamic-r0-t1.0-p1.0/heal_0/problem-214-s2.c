#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

double radians_to_degrees(double radians);

double radians_to_degrees(double radians) {
    return radians * (180.0 / M_PI);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <radians>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr = NULL;
    double radians = strtod(argv[1], &endptr);

    if (endptr == argv[1] || *endptr != '\0') {
        fprintf(stderr, "Error: Invalid numeric input.\n");
        return EXIT_FAILURE;
    }

    double degrees = radians_to_degrees(radians);
    
    if (printf("%.6f\n", degrees) < 0) {
        fprintf(stderr, "Error: Output failed.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}