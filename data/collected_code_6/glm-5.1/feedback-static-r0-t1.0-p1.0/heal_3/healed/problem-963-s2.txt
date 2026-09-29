#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

double calculate_discriminant(double a, double b, double c) {
    return (b * b) - (4.0 * a * c);
}

int main(int argc, char * const * argv) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <a> <b> <c>\n", argv[0]);
        return EXIT_FAILURE;
    }

    bool parse_error = false;
    char *endptr_a, *endptr_b, *endptr_c;

    double a = strtod(argv[1], &endptr_a);
    if (argv[1] == endptr_a) parse_error = true;

    double b = strtod(argv[2], &endptr_b);
    if (argv[2] == endptr_b) parse_error = true;

    double c = strtod(argv[3], &endptr_c);
    if (argv[3] == endptr_c) parse_error = true;

    if (parse_error || *endptr_a != '\0' || *endptr_b != '\0' || *endptr_c != '\0') {
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