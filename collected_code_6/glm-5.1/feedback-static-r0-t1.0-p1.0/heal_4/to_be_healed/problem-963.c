#include <stdio.h>
#include <stdlib.h>

double calculate_discriminant(double a, double b, double c) {
    return (b * b) - (4.0 * a * c);
}

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[const]) {
    if (argc != 4) {
        return EXIT_FAILURE;
    }

    char *endptr_a = NULL;
    char *endptr_b = NULL;
    char *endptr_c = NULL;

    double a = strtod(argv[1], &endptr_a);
    double b = strtod(argv[2], &endptr_b);
    double c = strtod(argv[3], &endptr_c);

    if (endptr_a == argv[1] || endptr_b == argv[2] || endptr_c == argv[3] ||
        *endptr_a != '\0' || *endptr_b != '\0' || *endptr_c != '\0') {
        return EXIT_FAILURE;
    }

    if (a == 0.0) {
        return EXIT_FAILURE;
    }

    double discriminant = calculate_discriminant(a, b, c);
    printf("%f\n", discriminant);

    return EXIT_SUCCESS;
}