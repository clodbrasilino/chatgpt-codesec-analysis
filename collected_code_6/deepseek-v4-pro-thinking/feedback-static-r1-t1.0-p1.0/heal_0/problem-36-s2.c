#include <stdio.h>
#include <limits.h>

static unsigned long long abs_ull(long long value)
{
    if (value < 0)
        return (unsigned long long)(-(value + 1)) + 1ULL;
    return (unsigned long long)value;
}

int nth_fraction_digit(long long numerator, long long denominator, long long n)
{
    unsigned long long num;
    unsigned long long den;
    long long i;

    if (denominator == 0 || n <= 0)
        return -1;

    num = abs_ull(numerator);
    den = abs_ull(denominator);

    num %= den;

    for (i = 0; i < n; ++i)
    {
        if (num > ULLONG_MAX / 10ULL)
            return -1;

        num *= 10ULL;

        if (i == n - 1)
            return (int)(num / den);

        num %= den;
    }

    return -1;
}

int main(void)
{
    long long numerator;
    long long denominator;
    long long n;
    int digit;

    if (scanf("%lld %lld %lld", &numerator, &denominator, &n) != 3)
        return 1;

    digit = nth_fraction_digit(numerator, denominator, n);

    if (digit < 0)
        return 1;

    printf("%d\n", digit);

    return 0;
}