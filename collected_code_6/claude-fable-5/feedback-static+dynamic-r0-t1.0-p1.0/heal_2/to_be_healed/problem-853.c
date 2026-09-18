#include <stdio.h>
#include <stdlib.h>

long long sum_odd_factors(long long n);

long long sum_odd_factors(long long n)
{
    long long res;
    long long i;

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
            curr_term *= i;
            curr_sum += curr_term;
        }
        res *= curr_sum;
    }

    if (n > 1)
    {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 16923530597376 * 649658 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000000,time:106,execs:60,op:havoc,rep:2)
         */
        res *= (1 + n);
    }

    return res;
}

int main(void)
{
    long long n;
    long long result;

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

    result = sum_odd_factors(n);
    printf("Sum of odd factors of %lld is %lld\n", n, result);

    return EXIT_SUCCESS;
}