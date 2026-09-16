#include <stdio.h>
#include <stdlib.h>

int nth_digit(long long numerator, long long denominator, long long n, int *digit)
{
    long long remainder;
    long long i;

    if (digit == NULL) {
        return -1;
    }

    if (denominator == 0) {
        return -1;
    }

    if (n < 1) {
        return -1;
    }

    if (numerator < 0) {
        numerator = -numerator;
    }

    if (denominator < 0) {
        denominator = -denominator;
    }

    if (numerator >= denominator) {
        return -1;
    }

    remainder = numerator % denominator;

    for (i = 0; i < n - 1; i++) {
        remainder = (remainder * 10) % denominator;
    }

    *digit = (int)((remainder * 10) / denominator);

    return 0;
}

int main(void)
{
    long long numerator;
    long long denominator;
    long long n;
    int digit;
    int result;

    printf("Enter numerator: ");
    if (scanf("%lld", &numerator) != 1) {
        fprintf(stderr, "Invalid input for numerator.\n");
        return EXIT_FAILURE;
    }

    printf("Enter denominator: ");
    if (scanf("%lld", &denominator) != 1) {
        fprintf(stderr, "Invalid input for denominator.\n");
        return EXIT_FAILURE;
    }

    printf("Enter n: ");
    if (scanf("%lld", &n) != 1) {
        fprintf(stderr, "Invalid input for n.\n");
        return EXIT_FAILURE;
    }

    result = nth_digit(numerator, denominator, n, &digit);

    if (result != 0) {
        fprintf(stderr, "Error: invalid arguments (denominator must be nonzero, n >= 1, and fraction must be proper).\n");
        return EXIT_FAILURE;
    }

    printf("The digit at position %lld is: %d\n", n, digit);

    return EXIT_SUCCESS;
}