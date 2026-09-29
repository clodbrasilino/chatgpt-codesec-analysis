#include <stdio.h>
#include <stdlib.h>

int last_two_digits_of_factorial(int n)
{
    int result;
    int i;

    if (n < 0)
    {
        return -1;
    }

    if (n >= 10)
    {
        return 0;
    }

    result = 1;
    for (i = 2; i <= n; i++)
    {
        result = (result * i) % 100;
    }

    return result;
}

int main(void)
{
    int number;
    int digits;
    int scan_result;

    printf("Enter a non-negative integer: ");
    scan_result = scanf("%d", &number);

    if (scan_result != 1)
    {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    digits = last_two_digits_of_factorial(number);

    if (digits < 0)
    {
        fprintf(stderr, "Error: factorial is not defined for negative numbers.\n");
        return EXIT_FAILURE;
    }

    printf("Last two digits of %d! are: %02d\n", number, digits);

    return EXIT_SUCCESS;
}