#include <stdio.h>
#include <limits.h>

long long sum_of_divisors(long long n)
{
    if (n <= 0)
    {
        return 0;
    }

    long long sum = 0;
    long long i = 1;

    while (i <= n / i)
    {
        if (n % i == 0)
        {
            long long pair = n / i;

            if (pair == i)
            {
                if (sum > LLONG_MAX - i)
                {
                    return -1;
                }
                sum += i;
            }
            else
            {
                if (sum > LLONG_MAX - i - pair)
                {
                    return -1;
                }
                sum += i + pair;
            }
        }
        i++;
    }

    return sum;
}

int main(void)
{
    long long num = 0;

    printf("Enter a positive integer: ");
    if (scanf("%lld", &num) != 1)
    {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    if (num <= 0)
    {
        fprintf(stderr, "Number must be positive\n");
        return 1;
    }

    long long result = sum_of_divisors(num);

    if (result == -1)
    {
        fprintf(stderr, "Overflow occurred\n");
        return 1;
    }

    printf("Sum of divisors of %lld is %lld\n", num, result);

    return 0;
}