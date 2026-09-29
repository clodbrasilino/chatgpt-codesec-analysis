#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int count_digits(long long num)
{
    int count = 0;

    if (num == 0)
    {
        return 1;
    }

    while (num != 0)
    {
        num /= 10;
        count++;
    }

    return count;
}

static long long int_power(int base, int exp)
{
    long long result = 1;
    int i;

    for (i = 0; i < exp; i++)
    {
        if (base != 0 && result > LLONG_MAX / base)
        {
            return -1;
        }
        result *= (long long)base;
    }

    return result;
}

static int is_armstrong(long long num)
{
    long long sum = 0;
    long long temp;
    int digits;

    if (num < 0)
    {
        return 0;
    }

    digits = count_digits(num);
    temp = num;

    while (temp != 0)
    {
        int digit = (int)(temp % 10);
        long long power = int_power(digit, digits);

        if (power < 0)
        {
            return 0;
        }

        if (sum > LLONG_MAX - power)
        {
            return 0;
        }

        sum += power;
        temp /= 10;
    }

    return (sum == num) ? 1 : 0;
}

int main(void)
{
    long long number = 0;
    int scan_result;

    printf("Enter a non-negative integer: ");
    scan_result = scanf("%lld", &number);

    if (scan_result != 1)
    {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (number < 0)
    {
        fprintf(stderr, "Error: number must be non-negative.\n");
        return EXIT_FAILURE;
    }

    if (is_armstrong(number))
    {
        printf("%lld is an Armstrong number.\n", number);
    }
    else
    {
        printf("%lld is not an Armstrong number.\n", number);
    }

    return EXIT_SUCCESS;
}