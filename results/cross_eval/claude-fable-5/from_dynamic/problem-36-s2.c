#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int find_nth_digit(long long numerator, long long denominator, long long n, int *digit);

int find_nth_digit(long long numerator, long long denominator, long long n, int *digit)
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
    if (numerator < 0 || denominator < 0) {
        return -1;
    }
    if (numerator >= denominator) {
        return -1;
    }

    remainder = numerator % denominator;
    for (i = 0; i < n; i++) {
        if (remainder > (LLONG_MAX / 10)) {
            return -1;
        }
        remainder = remainder * 10;
        if (i == n - 1) {
            *digit = (int)(remainder / denominator);
        }
        remainder = remainder % denominator;
    }

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

    result = find_nth_digit(numerator, denominator, n, &digit);
    if (result != 0) {
        fprintf(stderr, "Error: invalid arguments (need 0 <= numerator < denominator, denominator != 0, n >= 1).\n");
        return EXIT_FAILURE;
    }

    printf("The digit at position %lld is: %d\n", n, digit);
    return EXIT_SUCCESS;
}