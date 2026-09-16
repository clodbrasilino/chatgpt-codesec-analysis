#include <stdio.h>
#include <stdlib.h>

static long long sum_odd_factors(long long n)
{
    long long result;
    long long i;

    if (n <= 0)
    {
        return 0;
    }

    while (n % 2 == 0)
    {
        n /= 2;
    }

    result = 1;

    for (i = 3; i * i <= n; i += 2)
    {
        if (n % i == 0)
        {
            long long term_sum = 1;
            long long term = 1;

            while (n % i == 0)
            {
                n /= i;
                term *= i;
                term_sum += term;
            }
            result *= term_sum;
        }
    }

    if (n > 1)
    {
        result *= (n + 1);
    }

    return result;
}

int main(void)
{
    long long n;
    long long sum;

    printf("Enter a positive integer: ");

    if (scanf("%lld", &n) != 1)
    {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    if (n <= 0)
    {
        fprintf(stderr, "Error: number must be positive\n");
        return EXIT_FAILURE;
    }

    sum = sum_odd_factors(n);

    if (printf("Sum of odd factors of %lld is %lld\n", n, sum) < 0)
    {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}