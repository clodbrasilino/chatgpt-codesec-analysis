#include <stdio.h>
#include <limits.h>

int findNthDigit(long long numerator, long long denominator, int n)
{
    int i;
    int digit = -1;

    if (numerator < 0 || denominator <= 0 || numerator >= denominator || n <= 0) {
        return -1;
    }

    for (i = 0; i < n; i++) {
        if (numerator > LLONG_MAX / 10) {
            return -1;
        }
        numerator *= 10;
        digit = (int)(numerator / denominator);
        numerator %= denominator;
    }

    return digit;
}

int main(void)
{
    long long numerator;
    long long denominator;
    int n;
    int digit;

    printf("Enter numerator: ");
    if (scanf("%lld", &numerator) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }

    printf("Enter denominator: ");
    if (scanf("%lld", &denominator) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }

    printf("Enter the position n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }

    digit = findNthDigit(numerator, denominator, n);

    if (digit < 0) {
        fprintf(stderr, "Error: the fraction must be proper (0 <= numerator < denominator), denominator must be nonzero, and n must be positive.\n");
        return 1;
    }

    printf("Digit %d of %lld/%lld is: %d\n", n, numerator, denominator, digit);

    return 0;
}