#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>

double calculate_diameter(double radius) {
    if (radius < 0.0) {
        return -1.0;
    }
    return 2.0 * radius;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    double radius = 0.0;
    double diameter = 0.0;
    char *endptr;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <radius>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    radius = strtod(argv[1], &endptr);

    if (errno == ERANGE || endptr == argv[1] || *endptr != '\0') {
        fprintf(stderr, "Invalid input: Not a valid number\n");
        return EXIT_FAILURE;
    }

    if (isinf(radius) || isnan(radius)) {
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