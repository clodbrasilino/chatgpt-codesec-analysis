#include <stdio.h>
#include <limits.h>

static unsigned long long mul_ull_sat(unsigned long long a, unsigned long long b)
{
    if (a == 0 || b == 0) {
        return 0;
    }
    if (a > ULLONG_MAX / b) {
        return ULLONG_MAX;
    }
    return a * b;
}

static unsigned long long pow2_ull(int n)
{
    if (n >= 64) {
        return ULLONG_MAX;
    }
    return 1ULL << n;
}

static unsigned long long pow2_minus_one_ull(int n)
{
    if (n <= 0) {
        return 0;
    }
    if (n >= 64) {
        return ULLONG_MAX;
    }
    return (1ULL << n) - 1ULL;
}

static unsigned long long count_zero_subsequences(int zeros, int positives)
{
    unsigned long long zero_choices;
    unsigned long long positive_choices;

    if (zeros == 0) {
        return 0;
    }

    zero_choices = pow2_minus_one_ull(zeros);
    positive_choices = pow2_ull(positives);

    return mul_ull_sat(zero_choices, positive_choices);
}

int main(void)
{
    int zeros;
    int positives;

    if (scanf("%d %d", &zeros, &positives) != 2) {
        return 1;
    }

    if (zeros < 0 || positives < 0) {
        return 1;
    }

    printf("%llu\n", count_zero_subsequences(zeros, positives));

    return 0;
}