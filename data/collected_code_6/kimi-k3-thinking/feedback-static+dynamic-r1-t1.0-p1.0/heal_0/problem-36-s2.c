#include <stdio.h>

int find_nth_digit(int numerator, int denominator, int n)
{
    long long remainder;
    int digit = -1;
    int i;

    if (denominator <= 0 || numerator < 0 || numerator >= denominator || n <= 0)
    {
        return -1;
    }

    remainder = numerator % denominator;

    for (i = 0; i < n; i++)
    {
        remainder *= 10;
        digit = (int)(remainder / denominator);
        remainder %= denominator;
    }

    return digit;
}

int main(void)
{
    int numerator = 0;
    int denominator = 0;
    int n = 0;
    int result = 0;

    printf("Enter numerator: ");
    if (scanf("%d", &numerator) != 1)
    {
        fprintf(stderr, "Error: invalid input for numerator.\n");
        return 1;
    }

    printf("Enter denominator: ");
    if (scanf("%d", &denominator) != 1)
    {
        fprintf(stderr, "Error: invalid input for denominator.\n");
        return 1;
    }

    printf("Enter digit position n: ");
    if (scanf("%d", &n) != 1)
    {
        fprintf(stderr, "Error: invalid input for n.\n");
        return 1;
    }

    result = find_nth_digit(numerator, denominator, n);
    if (result < 0)
    {
        fprintf(stderr, "Error: invalid arguments. Require 0 <= numerator < denominator and n > 0.\n");
        return 1;
    }

    printf("The %dth digit of %d/%d is %d\n", n, numerator, denominator, result);

    return 0;
}