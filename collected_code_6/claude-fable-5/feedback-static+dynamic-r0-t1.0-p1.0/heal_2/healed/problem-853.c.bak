#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int safe_mul(long long a, long long b, long long *out);
static int safe_add(long long a, long long b, long long *out);
long long sum_odd_factors(long long n, int *overflow);

static int safe_mul(long long a, long long b, long long *out)
{
    if (a > 0 && b > 0 && a > LLONG_MAX / b)
    {
        return 0;
    }
    *out = a * b;
    return 1;
}

static int safe_add(long long a, long long b, long long *out)
{
    if (a > 0 && b > 0 && a > LLONG_MAX - b)
    {
        return 0;
    }
    *out = a + b;
    return 1;
}

long long sum_odd_factors(long long n, int *overflow)
{
    long long res;
    long long i;

    *overflow = 0;

    if (n <= 0)
    {
        return 0;
    }

    while (n % 2 == 0)
    {
        n /= 2;
    }

    res = 1;
    for (i = 3; i * i <= n; i += 2)
    {
        long long curr_sum = 1;
        long long curr_term = 1;
        while (n % i == 0)
        {
            n /= i;
            if (!safe_mul(curr_term, i, &curr_term))
            {
                *overflow = 1;
                return 0;
            }
            if (!safe_add(curr_sum, curr_term, &curr_sum))
            {
                *overflow = 1;
                return 0;
            }
        }
        if (!safe_mul(res, curr_sum, &res))
        {
            *overflow = 1;
            return 0;
        }
    }

    if (n > 1)
    {
        long long factor;
        if (!safe_add(1, n, &factor))
        {
            *overflow = 1;
            return 0;
        }
        if (!safe_mul(res, factor, &res))
        {
            *overflow = 1;
            return 0;
        }
    }

    return res;
}

int main(void)
{
    long long n;
    long long result;
    int overflow;

    printf("Enter a positive integer: ");
    if (scanf("%lld", &n) != 1)
    {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    if (n <= 0)
    {
        fprintf(stderr, "Error: input must be a positive integer\n");
        return EXIT_FAILURE;
    }

    result = sum_odd_factors(n, &overflow);
    if (overflow)
    {
        fprintf(stderr, "Error: result overflows long long\n");
        return EXIT_FAILURE;
    }

    printf("Sum of odd factors of %lld is %lld\n", n, result);

    return EXIT_SUCCESS;
}