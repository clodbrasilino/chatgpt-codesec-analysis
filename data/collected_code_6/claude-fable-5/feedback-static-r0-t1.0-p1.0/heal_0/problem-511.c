#include <stdio.h>
#include <stdlib.h>

long long min_sum_of_factors(long long num)
{
    long long sum = 0;
    long long i = 2;

    if (num < 2)
    {
        return num;
    }

    while (i * i <= num)
    {
        while (num % i == 0)
        {
            sum += i;
            num /= i;
        }
        i++;
    }

    if (num > 1)
    {
        sum += num;
    }

    return sum;
}

int main(void)
{
    long long n = 0;
    long long result = 0;

    printf("Enter a positive integer: ");

    if (scanf("%lld", &n) != 1)
    {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (n < 1)
    {
        fprintf(stderr, "Error: number must be a positive integer.\n");
        return EXIT_FAILURE;
    }

    result = min_sum_of_factors(n);

    printf("Minimum sum of factors of %lld is %lld\n", n, result);

    return EXIT_SUCCESS;
}