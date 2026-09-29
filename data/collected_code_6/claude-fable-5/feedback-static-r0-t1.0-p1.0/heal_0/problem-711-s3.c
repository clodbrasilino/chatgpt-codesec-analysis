#include <stdio.h>
#include <stdbool.h>

bool has_equal_digit_products(long long num);

bool has_equal_digit_products(long long num)
{
    long long even_product = 1;
    long long odd_product = 1;
    int position = 1;

    if (num < 0)
    {
        num = -num;
    }

    if (num == 0)
    {
        return false;
    }

    while (num > 0)
    {
        int digit = (int)(num % 10);

        if ((position % 2) == 0)
        {
            even_product *= digit;
        }
        else
        {
            odd_product *= digit;
        }

        num /= 10;
        position++;
    }

    return (even_product == odd_product);
}

int main(void)
{
    long long number = 0;
    int result;

    printf("Enter a number: ");

    result = scanf("%lld", &number);

    if (result != 1)
    {
        fprintf(stderr, "Error: invalid input.\n");
        return 1;
    }

    if (has_equal_digit_products(number))
    {
        printf("The products of digits at even and odd places are equal.\n");
    }
    else
    {
        printf("The products of digits at even and odd places are not equal.\n");
    }

    return 0;
}