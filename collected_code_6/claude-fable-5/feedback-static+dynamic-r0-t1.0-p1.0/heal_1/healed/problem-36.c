#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int nth_digit(long long numerator, long long denominator, long long n, int *digit)
{
    unsigned long long num;
    unsigned long long den;
    unsigned long long remainder;
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
        num = (unsigned long long)(-(numerator + 1)) + 1ULL;
    } else {
        num = (unsigned long long)numerator;
    }

    if (denominator < 0) {
        den = (unsigned long long)(-(denominator + 1)) + 1ULL;
    } else {
        den = (unsigned long long)denominator;
    }

    if (num >= den) {
        return -1;
    }

    if (den > ULLONG_MAX / 10ULL) {
        return -1;
    }

    remainder = num % den;

    for (i = 0; i < n - 1; i++) {
        remainder = (remainder * 10ULL) % den;
    }

    *digit = (int)((remainder * 10ULL) / den);

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