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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return EXIT_FAILURE;
    }

    char *endptr;
    radius = strtod(buffer, &endptr);

    if (endptr == buffer || *endptr != '\n' && *endptr != '\0') {
        return EXIT_FAILURE;
    }

    diameter = calculate_diameter(radius);

    if (diameter < 0.0) {
        return EXIT_FAILURE;
    }

    printf("%f\n", diameter);

    return EXIT_SUCCESS;
}