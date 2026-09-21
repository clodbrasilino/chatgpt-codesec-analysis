#include <stdio.h>
#include <stdlib.h>

double calculate_discriminant(double a, double b, double c) {
    return (b * b) - (4.0 * a * c);
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    double a, b, c;

    if (argc != 4) {
        fprintf(stderr, "Usage: %s <a> <b> <c>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr_a, *endptr_b, *endptr_c;

    a = strtod(argv[1], &endptr_a);
    b = strtod(argv[2], &endptr_b);
    c = strtod(argv[3], &endptr_c);

    if (*endptr_a != '\0' || *endptr_b != '\0' || *endptr_c != '\0') {
        fprintf(stderr, "Invalid input: Non-numeric characters detected.\n");
        return EXIT_FAILURE;
    }

    if (a == 0.0) {
        fprintf(stderr, "Coefficient 'a' cannot be zero for a quadratic equation.\n");
        return EXIT_FAILURE;
    }

    double discriminant = calculate_discriminant(a, b, c);

    printf("%.6f\n", discriminant);

    return EXIT_SUCCESS;
}