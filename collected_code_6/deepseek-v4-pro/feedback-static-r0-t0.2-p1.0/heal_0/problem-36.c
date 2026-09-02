#include <stdio.h>
#include <stdlib.h>

int nth_digit_of_fraction(int numerator, int denominator, int n) {
    if (denominator == 0) {
        return -1;
    }
    if (numerator < 0) {
        numerator = -numerator;
    }
    if (denominator < 0) {
        denominator = -denominator;
    }
    if (n < 1) {
        return -1;
    }

    long long remainder = numerator % denominator;
    int digit = 0;

    for (int i = 0; i < n; i++) {
        remainder *= 10;
        digit = remainder / denominator;
        remainder %= denominator;
    }

    return digit;
}

int main(void) {
    int numerator, denominator, n;

    printf("Enter numerator: ");
    if (scanf("%d", &numerator) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    printf("Enter denominator: ");
    if (scanf("%d", &denominator) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    int result = nth_digit_of_fraction(numerator, denominator, n);
    if (result == -1) {
        fprintf(stderr, "Invalid arguments\n");
        return EXIT_FAILURE;
    }

    printf("The %d-th digit after decimal point is: %d\n", n, result);

    return EXIT_SUCCESS;
}