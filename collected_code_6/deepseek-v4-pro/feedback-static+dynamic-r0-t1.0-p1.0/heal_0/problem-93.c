#include <stdio.h>
#include <stdlib.h>

double power(double a, int b) {
    if (a == 0.0 && b <= 0) {
        fprintf(stderr, "Error: 0 cannot be raised to a non-positive power.\n");
        exit(EXIT_FAILURE);
    }

    if (b == 0) {
        return 1.0;
    }

    int negative_exponent = 0;
    if (b < 0) {
        negative_exponent = 1;
        b = -b;
        if (b < 0) {
            fprintf(stderr, "Error: integer overflow while negating exponent.\n");
            exit(EXIT_FAILURE);
        }
    }

    double result = 1.0;
    double base = a;
    int exp = b;

    while (exp > 0) {
        if (exp & 1) {
            result *= base;
        }
        base *= base;
        exp >>= 1;
    }

    return negative_exponent ? 1.0 / result : result;
}

int main(void) {
    double a;
    int b;

    printf("Enter base (double): ");
    if (scanf("%lf", &a) != 1) {
        fprintf(stderr, "Error: invalid input for base.\n");
        return EXIT_FAILURE;
    }

    printf("Enter exponent (int): ");
    if (scanf("%d", &b) != 1) {
        fprintf(stderr, "Error: invalid input for exponent.\n");
        return EXIT_FAILURE;
    }

    double result = power(a, b);
    printf("%.10g ^ %d = %.10g\n", a, b, result);

    return EXIT_SUCCESS;
}