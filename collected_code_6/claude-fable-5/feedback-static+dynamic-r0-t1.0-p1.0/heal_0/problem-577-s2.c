#include <stdio.h>
#include <stdlib.h>

int last_digit_of_factorial(int n);

int last_digit_of_factorial(int n)
{
    if (n < 0)
    {
        return -1;
    }

    switch (n)
    {
        case 0:
        case 1:
            return 1;
        case 2:
            return 2;
        case 3:
            return 6;
        case 4:
            return 4;
        default:
            return 0;
    }
}

int main(void)
{
    int number = 0;
    int result = 0;

    printf("Enter a non-negative integer: ");

    if (scanf("%d", &number) != 1)
    {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    result = last_digit_of_factorial(number);

    if (result < 0)
    {
        fprintf(stderr, "Error: factorial is not defined for negative numbers.\n");
        return EXIT_FAILURE;
    }

    printf("The last digit of %d! is %d\n", number, result);

    return EXIT_SUCCESS;
}