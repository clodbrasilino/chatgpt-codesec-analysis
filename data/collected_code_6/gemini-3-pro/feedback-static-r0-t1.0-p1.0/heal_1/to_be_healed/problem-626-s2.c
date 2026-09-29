#include <stdio.h>
#include <stdlib.h>

double largest_triangle_area(double radius);

double largest_triangle_area(double radius) {
    if (radius < 0.0) {
        return -1.0;
    }
    return radius * radius;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[64];
    double radius;
    double area;
    char *endptr;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        return EXIT_FAILURE;
    }

    radius = strtod(input, &endptr);
    if (endptr == input) {
        return EXIT_FAILURE;
    }

    area = largest_triangle_area(radius);
    if (area < 0.0) {
        return EXIT_FAILURE;
    }

    printf("%f\n", area);

    return EXIT_SUCCESS;
}