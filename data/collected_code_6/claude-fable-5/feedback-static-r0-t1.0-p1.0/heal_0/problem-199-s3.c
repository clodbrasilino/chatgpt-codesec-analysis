#include <stdio.h>
#include <stdlib.h>

static unsigned long highest_power_of_two(unsigned long n)
{
    unsigned long result = 0UL;

    if (n == 0UL) {
        return 0UL;
    }

    result = 1UL;
    while ((result << 1) != 0UL && (result << 1) <= n) {
        result <<= 1;
    }

    return result;
}

int main(void)
{
    unsigned long number = 0UL;
    unsigned long result = 0UL;
    int scan_status = 0;

    printf("Enter a positive number: ");
    scan_status = scanf("%lu", &number);

    if (scan_status != 1) {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    if (number == 0UL) {
        fprintf(stderr, "Error: no power of 2 is less than or equal to 0\n");
        return EXIT_FAILURE;
    }

    result = highest_power_of_two(number);
    printf("Highest power of 2 <= %lu is %lu\n", number, result);

    return EXIT_SUCCESS;
}