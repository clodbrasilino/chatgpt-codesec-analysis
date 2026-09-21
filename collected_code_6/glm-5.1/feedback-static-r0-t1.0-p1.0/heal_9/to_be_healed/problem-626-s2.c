#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

double find_largest_triangle_area(double radius) {
    if (radius < 0.0) {
        return -1.0;
    }
    return radius * radius;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }

    char *endptr;
    errno = 0;
    double radius = strtod(argv[1], &endptr);

    if (errno != 0 || endptr == argv[1] || *endptr != '\0') {
        return EXIT_FAILURE;
    }

    double area = find_largest_triangle_area(radius);

    if (area < 0.0) {
        return EXIT_FAILURE;
    }

    printf("%.6f\n", area);

    return EXIT_SUCCESS;
}