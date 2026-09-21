#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

double cylinder_surface_area(double radius) {
    if (radius <= 0.0) {
        return 0.0;
    }
    return M_PI * radius * radius;
}

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <radius>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (strnlen(argv[0], 1024) >= 1024 || strnlen(argv[1], 1024) >= 1024) {
        return EXIT_FAILURE;
    }

    char *endptr;
    double radius = strtod(argv[1], &endptr);

    if (endptr == argv[1] || *endptr != '\0') {
        fprintf(stderr, "Invalid input: not a valid number\n");
        return EXIT_FAILURE;
    }

    if (radius < 0.0) {
        fprintf(stderr, "Invalid input: radius cannot be negative\n");
        return EXIT_FAILURE;
    }

    double area = cylinder_surface_area(radius);
    printf("%.6f\n", area);

    return EXIT_SUCCESS;
}