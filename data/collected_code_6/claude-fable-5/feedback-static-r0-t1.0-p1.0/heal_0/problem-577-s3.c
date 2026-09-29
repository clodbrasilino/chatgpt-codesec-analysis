#include <stdio.h>
#include <stdlib.h>

int last_digit_of_factorial(unsigned int n)
{
    if (n == 0U || n == 1U)
    {
        return 1;
    }
    if (n == 2U)
    {
        return 2;
    }
    if (n == 3U)
    {
        return 6;
    }
    if (n == 4U)
    {
        return 4;
    }
    return 0;
}

int main(void)
{
    unsigned int number = 0U;
    int result = 0;

    printf("Enter a non-negative integer: ");
    if (scanf("%u", &number) != 1)
    {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    result = last_digit_of_factorial(number);
    printf("The last digit of %u! is %d\n", number, result);

    return EXIT_SUCCESS;
}