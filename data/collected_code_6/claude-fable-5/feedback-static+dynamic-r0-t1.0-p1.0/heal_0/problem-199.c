#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static unsigned int highest_power_of_two(unsigned int n)
{
    unsigned int result = 0U;

    if (n == 0U)
    {
        return 0U;
    }

    result = 1U;
    while ((result <= (n >> 1U)) && (result <= (UINT_MAX >> 1U)))
    {
        result <<= 1U;
    }

    return result;
}

int main(void)
{
    unsigned int number = 0U;
    unsigned int answer = 0U;
    int scan_result = 0;

    printf("Enter a positive integer: ");

    scan_result = scanf("%u", &number);
    if (scan_result != 1)
    {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (number == 0U)
    {
        fprintf(stderr, "Error: no power of 2 is less than or equal to 0.\n");
        return EXIT_FAILURE;
    }

    answer = highest_power_of_two(number);
    printf("Highest power of 2 less than or equal to %u is %u\n", number, answer);

    return EXIT_SUCCESS;
}