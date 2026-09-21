#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double calculate_tetrahedron_area(double a) {
    if (a <= 0.0) {
        return -1.0;
    }
    return sqrt(3.0) * a * a;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <edge_length>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    double a = strtod(argv[1], &endptr);

    if (endptr == argv[1] || *endptr != '\0') {
        fprintf(stderr, "Invalid input: not a valid number\n");
        return EXIT_FAILURE;
    }

    double area = calculate_tetrahedron_area(a);

    if (area < 0.0) {
        fprintf(stderr, "Invalid input: edge length must be strictly positive\n");
        return EXIT_FAILURE;
    }

    printf("%f\n", area);

    return EXIT_SUCCESS;
}