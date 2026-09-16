#include <stdio.h>
#include <stdlib.h>

long sum_of_divisors(long n)
{
    long total = 0;
    long i;

    if (n <= 0)
    {
        return 0;
    }

    for (i = 1; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            total += i;
            if (i != n / i)
            {
                total += n / i;
            }
        }
    }

    return total;
}

int are_divisor_sums_equal(long a, long b)
{
    return sum_of_divisors(a) == sum_of_divisors(b);
}

int main(void)
{
    long num1 = 0;
    long num2 = 0;

    printf("Enter first number: ");
    if (scanf("%ld", &num1) != 1)
    {
        fprintf(stderr, "Invalid input for first number.\n");
        return EXIT_FAILURE;
    }

    printf("Enter second number: ");
    if (scanf("%ld", &num2) != 1)
    {
        fprintf(stderr, "Invalid input for second number.\n");
        return EXIT_FAILURE;
    }

    if (num1 <= 0 || num2 <= 0)
    {
        fprintf(stderr, "Numbers must be positive.\n");
        return EXIT_FAILURE;
    }

    if (are_divisor_sums_equal(num1, num2))
    {
        printf("The sum of divisors of %ld and %ld are the same.\n", num1, num2);
    }
    else
    {
        printf("The sum of divisors of %ld and %ld are not the same.\n", num1, num2);
    }

    return EXIT_SUCCESS;
}