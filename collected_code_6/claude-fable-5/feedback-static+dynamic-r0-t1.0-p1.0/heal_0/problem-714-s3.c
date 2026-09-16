#include <stdio.h>
#include <stdlib.h>

static int count_distinct_prime_power_factors(long long n)
{
    int count = 0;
    long long divisor = 2;

    if (n < 2)
    {
        return 0;
    }

    while (divisor * divisor <= n)
    {
        if (n % divisor == 0)
        {
            int exponent = 0;
            while (n % divisor == 0)
            {
                n /= divisor;
                exponent++;
            }
            count += exponent;
        }
        divisor++;
    }

    if (n > 1)
    {
        count += 1;
    }

    return count;
}

int main(void)
{
    long long number = 0;
    int result = 0;

    printf("Enter a positive integer: ");
    if (scanf("%lld", &number) != 1)
    {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (number < 1)
    {
        fprintf(stderr, "Error: input must be a positive integer.\n");
        return EXIT_FAILURE;
    }

    result = count_distinct_prime_power_factors(number);
    printf("Number of distinct prime power factors of %lld: %d\n", number, result);

    return EXIT_SUCCESS;
}