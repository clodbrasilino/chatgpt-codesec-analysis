#include <stdio.h>
#include <stdbool.h>

bool has_equal_digit_products(long long num);

bool has_equal_digit_products(long long num)
{
    unsigned long long value;
    unsigned long long even_product = 1;
    unsigned long long odd_product = 1;
    int position = 1;

    if (num < 0)
    {
        value = (unsigned long long)(-(num + 1)) + 1ULL;
    }
    else
    {
        value = (unsigned long long)num;
    }

    if (value == 0)
    {
        return false;
    }

    while (value > 0)
    {
        unsigned long long digit = value % 10ULL;

        if ((position % 2) == 0)
        {
            even_product *= digit;
        }
        else
        {
            odd_product *= digit;
        }

        value /= 10ULL;
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