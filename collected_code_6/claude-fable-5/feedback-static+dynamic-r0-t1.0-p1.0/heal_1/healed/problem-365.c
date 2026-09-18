#include <stdio.h>
#include <stdlib.h>

int count_digits(long long number)
{
    int count = 0;
    unsigned long long magnitude;

    if (number == 0)
    {
        return 1;
    }

    if (number < 0)
    {
        magnitude = (unsigned long long)(-(number + 1)) + 1ULL;
    }
    else
    {
        magnitude = (unsigned long long)number;
    }

    while (magnitude > 0)
    {
        magnitude /= 10;
        count++;
    }

    return count;
}

int main(void)
{
    long long number = 0;
    int result = 0;

    printf("Enter an integer: ");

    if (scanf("%lld", &number) != 1)
    {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    result = count_digits(number);

    printf("Number of digits: %d\n", result);

    return EXIT_SUCCESS;
}