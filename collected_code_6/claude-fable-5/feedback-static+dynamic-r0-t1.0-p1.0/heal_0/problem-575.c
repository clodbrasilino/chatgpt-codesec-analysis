#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long nth_non_multiple(long long n, long long divisor)
{
    long long offset;

    if (n < 1 || divisor < 2) {
        return -1;
    }

    offset = (n - 1) / (divisor - 1);

    if (n > LLONG_MAX - offset) {
        return -1;
    }

    return n + offset;
}

int main(void)
{
    long long n;
    long long divisor;
    long long result;
    int scanned;

    printf("Enter the divisor: ");
    scanned = scanf("%lld", &divisor);
    if (scanned != 1) {
        fprintf(stderr, "Invalid input for divisor.\n");
        return EXIT_FAILURE;
    }

    printf("Enter n: ");
    scanned = scanf("%lld", &n);
    if (scanned != 1) {
        fprintf(stderr, "Invalid input for n.\n");
        return EXIT_FAILURE;
    }

    result = nth_non_multiple(n, divisor);
    if (result < 0) {
        fprintf(stderr, "Invalid arguments: n must be >= 1 and divisor must be >= 2, and the result must not overflow.\n");
        return EXIT_FAILURE;
    }

    printf("The %lld-th number that is not a multiple of %lld is: %lld\n", n, divisor, result);

    return EXIT_SUCCESS;
}