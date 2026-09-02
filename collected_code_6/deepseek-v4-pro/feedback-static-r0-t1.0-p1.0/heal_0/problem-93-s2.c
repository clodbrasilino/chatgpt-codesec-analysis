#include <stdio.h>
#include <stdlib.h>

double power(double a, int b) {
    if (a == 0.0 && b <= 0) {
        fprintf(stderr, "Error: 0 cannot be raised to a non-positive power\n");
        exit(EXIT_FAILURE);
    }

    if (b == 0) {
        return 1.0;
    }

    int abs_b = abs(b);
    double result = 1.0;
    double base = a;

    while (abs_b > 0) {
        if (abs_b & 1) {
            result *= base;
        }
        base *= base;
        abs_b >>= 1;
    }

    if (b < 0) {
        if (result == 0.0) {
            fprintf(stderr, "Error: division by zero\n");
            exit(EXIT_FAILURE);
        }
        return 1.0 / result;
    }

    return result;
}

int main(void) {
    double a;
    int b;

    printf("Enter base (a): ");
    if (scanf("%lf", &a) != 1) {
        fprintf(stderr, "Invalid input for base\n");
        return EXIT_FAILURE;
    }

    printf("Enter exponent (b): ");
    if (scanf("%d", &b) != 1) {
        fprintf(stderr, "Invalid input for exponent\n");
        return EXIT_FAILURE;
    }

    double result = power(a, b);
    printf("%.10g^%d = %.10g\n", a, b, result);

    return EXIT_SUCCESS;
}