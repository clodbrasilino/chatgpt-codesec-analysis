#include <stdio.h>
#include <stdlib.h>

int last_digit_of_factorial(int n)
{
    if (n < 0)
    {
        return -1;
    }

    if (n < 5)
    {
        int digits[5] = {1, 1, 2, 6, 4};
        return digits[n];
    }

    return 0;
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
        fprintf(stderr, "Error: number must be non-negative.\n");
        return EXIT_FAILURE;
    }

    printf("The last digit of %d! is %d\n", number, result);

    return EXIT_SUCCESS;
}