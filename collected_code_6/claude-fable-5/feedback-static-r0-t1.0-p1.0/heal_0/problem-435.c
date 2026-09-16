#include <stdio.h>
#include <stdlib.h>

int last_digit(long long number)
{
    long long remainder = number % 10;
    if (remainder < 0) {
        remainder = -remainder;
    }
    return (int)remainder;
}

int main(void)
{
    long long number = 0;
    int result = 0;

    printf("Enter a number: ");
    if (scanf("%lld", &number) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    result = last_digit(number);
    printf("The last digit of %lld is %d\n", number, result);

    return EXIT_SUCCESS;
}