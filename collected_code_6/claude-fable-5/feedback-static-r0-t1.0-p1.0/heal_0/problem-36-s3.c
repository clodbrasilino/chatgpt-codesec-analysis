#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int find_nth_digit(long long numerator, long long denominator, long long n, int *error);

int find_nth_digit(long long numerator, long long denominator, long long n, int *error)
{
    long long remainder;
    long long digit = 0;
    long long i;

    if (error == NULL) {
        return -1;
    }

    *error = 0;

    if (denominator == 0) {
        *error = 1;
        return -1;
    }

    if (n < 1) {
        *error = 1;
        return -1;
    }

    if (numerator < 0 || denominator < 0) {
        *error = 1;
        return -1;
    }

    if (numerator >= denominator) {
        *error = 1;
        return -1;
    }

    if (denominator > LLONG_MAX / 10) {
        *error = 1;
        return -1;
    }

    remainder = numerator % denominator;

    for (i = 0; i < n; i++) {
        remainder = remainder * 10;
        digit = remainder / denominator;
        remainder = remainder % denominator;
    }

    return (int)digit;
}

int main(void)
{
    long long numerator;
    long long denominator;
    long long n;
    int error = 0;
    int digit;

    printf("Enter numerator: ");
    if (scanf("%lld", &numerator) != 1) {
        fprintf(stderr, "Invalid input for numerator\n");
        return EXIT_FAILURE;
    }

    printf("Enter denominator: ");
    if (scanf("%lld", &denominator) != 1) {
        fprintf(stderr, "Invalid input for denominator\n");
        return EXIT_FAILURE;
    }

    printf("Enter n: ");
    if (scanf("%lld", &n) != 1) {
        fprintf(stderr, "Invalid input for n\n");
        return EXIT_FAILURE;
    }

    digit = find_nth_digit(numerator, denominator, n, &error);

    if (error != 0) {
        fprintf(stderr, "Error: invalid arguments (need 0 <= numerator < denominator, denominator != 0, n >= 1)\n");
        return EXIT_FAILURE;
    }

    printf("The digit at position %lld of %lld/%lld is: %d\n", n, numerator, denominator, digit);

    return EXIT_SUCCESS;
}