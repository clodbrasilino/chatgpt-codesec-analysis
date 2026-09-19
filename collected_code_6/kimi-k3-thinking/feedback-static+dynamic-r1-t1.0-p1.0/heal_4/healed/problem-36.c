#include <stdio.h>

int findNthDigit(long long numerator, long long denominator, int n)
{
    int i;
    int digit;

    if (numerator < 0 || denominator <= 0 || n <= 0) {
        return -1;
    }

    numerator %= denominator;

    digit = 0;
    for (i = 0; i < n; i++) {
        __int128 scaled = (__int128)numerator * 10;
        digit = (int)(scaled / denominator);
        numerator = (long long)(scaled % denominator);
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
        fprintf(stderr, "Error: invalid input.\n");
        return 1;
    }

    printf("%d\n", digit);

    return 0;
}