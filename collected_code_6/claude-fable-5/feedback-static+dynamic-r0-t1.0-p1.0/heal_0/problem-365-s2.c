#include <stdio.h>
#include <stdlib.h>

int count_digits(long long number)
{
    int count = 1;

    if (number < 0) {
        number = -number;
    }

    while (number >= 10) {
        number /= 10;
        count++;
    }

    return count;
}

int main(void)
{
    long long number = 0;
    int result = 0;

    printf("Enter a number: ");

    if (scanf("%lld", &number) != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    result = count_digits(number);

    printf("The number %lld has %d digit(s).\n", number, result);

    return EXIT_SUCCESS;
}