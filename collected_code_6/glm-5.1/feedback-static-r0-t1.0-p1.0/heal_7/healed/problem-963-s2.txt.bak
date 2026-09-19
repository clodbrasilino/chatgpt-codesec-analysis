#include <stdio.h>
#include <stdlib.h>

double calculate_discriminant(double a, double b, double c) {
    return (b * b) - (4.0 * a * c);
}

int main(int argc, char const * const argv[const]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <a> <b> <c>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr_a, *endptr_b, *endptr_c;

    double a = strtod(argv[1], &endptr_a);
    double b = strtod(argv[2], &endptr_b);
    double c = strtod(argv[3], &endptr_c);

    if (*endptr_a != '\0' || *endptr_b != '\0' || *endptr_c != '\0') {
        fprintf(stderr, "Invalid input format. Expected numerical values.\n");
        return EXIT_FAILURE;
    }

    if (a == 0.0) {
        fprintf(stderr, "Coefficient 'a' cannot be zero in a quadratic equation.\n");
        return EXIT_FAILURE;
    }

    double discriminant = calculate_discriminant(a, b, c);

    printf("%f\n", discriminant);

    return EXIT_SUCCESS;
}