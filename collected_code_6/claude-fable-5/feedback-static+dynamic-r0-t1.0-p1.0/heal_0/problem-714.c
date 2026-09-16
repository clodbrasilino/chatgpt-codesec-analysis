#include <stdio.h>
#include <stdlib.h>

static int count_distinct_prime_powers(long long n)
{
    int count = 0;
    long long i;

    if (n < 2)
    {
        return 0;
    }

    for (i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            int exponent = 0;
            while (n % i == 0)
            {
                n /= i;
                exponent++;
            }
            count += exponent;
        }
    }

    if (n > 1)
    {
        count += 1;
    }

    return count;
}

int main(void)
{
    long long n = 0;
    int result;

    printf("Enter a positive integer: ");
    if (scanf("%lld", &n) != 1)
    {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (n < 1)
    {
        fprintf(stderr, "Error: number must be positive.\n");
        return EXIT_FAILURE;
    }

    result = count_distinct_prime_powers(n);
    printf("Number of distinct powers of prime factors: %d\n", result);

    return EXIT_SUCCESS;
}