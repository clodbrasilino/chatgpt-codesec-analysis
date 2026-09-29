#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

static bool add_would_overflow(long a, long b)
{
    return (b > 0 && a > LONG_MAX - b) || (b < 0 && a < LONG_MIN - b);
}

static bool sum_of_divisors(long n, long *result)
{
    long total;
    long i;
    long quotient;

    if (n <= 0 || result == NULL) {
        return false;
    }

    total = 0;
    for (i = 1; i <= n / i; i++) {
        if (n % i == 0) {
            if (add_would_overflow(total, i)) {
                return false;
            }
            total += i;
            quotient = n / i;
            if (i != quotient) {
                if (add_would_overflow(total, quotient)) {
                    return false;
                }
                total += quotient;
            }
        }
    }

    *result = total;
    return true;
}

static bool compare_divisor_sums(long a, long b, bool *is_same)
{
    long sum_a;
    long sum_b;

    if (is_same == NULL) {
        return false;
    }

    if (!sum_of_divisors(a, &sum_a)) {
        return false;
    }

    if (!sum_of_divisors(b, &sum_b)) {
        return false;
    }

    *is_same = (sum_a == sum_b);
    return true;
}

int main(void)
{
    long a;
    long b;
    bool is_same;

    printf("Enter two positive integers: ");
    if (scanf("%ld %ld", &a, &b) != 2) {
        fprintf(stderr, "Error: invalid input.\n");
        return 1;
    }

    if (a <= 0 || b <= 0) {
        fprintf(stderr, "Error: inputs must be positive integers.\n");
        return 1;
    }

    if (!compare_divisor_sums(a, b, &is_same)) {
        fprintf(stderr, "Error: computation failed due to overflow.\n");
        return 1;
    }

    if (is_same) {
        printf("The sums of divisors of %ld and %ld are the same.\n", a, b);
    } else {
        printf("The sums of divisors of %ld and %ld are not the same.\n", a, b);
    }

    return 0;
}