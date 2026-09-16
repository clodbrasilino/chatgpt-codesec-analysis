#include <stdio.h>
#include <stdlib.h>

static int count_digits(long n)
{
    int count = 0;

    if (n == 0)
    {
        return 1;
    }

    while (n > 0)
    {
        count++;
        n /= 10;
    }

    return count;
}

static long int_power(long base, int exp)
{
    long result = 1;
    int i;

    for (i = 0; i < exp; i++)
    {
        result *= base;
    }

    return result;
}

static int is_armstrong(long num)
{
    long sum = 0;
    long temp = num;
    int digits;

    if (num < 0)
    {
        return 0;
    }

    digits = count_digits(num);

    while (temp > 0)
    {
        long digit = temp % 10;
        sum += int_power(digit, digits);
        temp /= 10;
    }

    return (sum == num) ? 1 : 0;
}

int main(void)
{
    long number = 0;

    printf("Enter a non-negative integer: ");

    if (scanf("%ld", &number) != 1)
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
        printf("%ld is an Armstrong number.\n", number);
    }
    else
    {
        printf("%ld is not an Armstrong number.\n", number);
    }

    return EXIT_SUCCESS;
}