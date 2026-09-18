#include <stdio.h>
#include <math.h>
#include <stdlib.h>

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
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 8249225494113808406 + 1350851717672992089 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000002,time:33344,execs:19925,op:havoc,rep:5)
         */
        sum += int_power(digit, digits);
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