#include <stdio.h>
#include <limits.h>

int findNthDigit(long long numerator, long long denominator, int n)
{
    int i;
    int j;
    int digit = -1;
    long long remainder;

    if (numerator < 0 || denominator <= 0 || numerator >= denominator || n <= 0) {
        return -1;
    }

    for (i = 0; i < n; i++) {
        digit = 0;
        remainder = 0;
        for (j = 0; j < 10; j++) {
            if (remainder >= denominator - numerator) {
                remainder -= denominator - numerator;
                digit++;
            } else {
                remainder += numerator;
            }
        }
        numerator = remainder;
    }

    return digit;
}

int main(void)
{
    long long numerator;
    long long denominator;
    int n;
    int digit;

    if (scanf("%lld %lld %d", &numerator, &denominator, &n) != 3) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }

    digit = findNthDigit(numerator, denominator, n);

    if (digit < 0) {
        fprintf(stderr, "Error: the fraction must be proper (0 <= numerator < denominator), denominator must be nonzero, and n must be positive.\n");
        return 1;
    }

    printf("%d\n", digit);

    return 0;
}