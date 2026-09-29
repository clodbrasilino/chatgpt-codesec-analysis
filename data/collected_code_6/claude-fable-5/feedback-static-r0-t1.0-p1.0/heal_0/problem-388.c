#include <stdio.h>
#include <stdlib.h>

unsigned int highest_power_of_two(unsigned int n)
{
    unsigned int result;

    if (n == 0U) {
        return 0U;
    }

    result = 1U;
    while (result <= n / 2U) {
        result *= 2U;
    }

    return result;
}

int main(void)
{
    unsigned int n;
    unsigned int result;
    int scan_status;

    printf("Enter a positive integer: ");
    scan_status = scanf("%u", &n);

    if (scan_status != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (n == 0U) {
        fprintf(stderr, "Error: no power of 2 is less than or equal to 0.\n");
        return EXIT_FAILURE;
    }

    result = highest_power_of_two(n);
    printf("The highest power of 2 less than or equal to %u is %u\n", n, result);

    return EXIT_SUCCESS;
}