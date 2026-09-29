#include <stdio.h>
#include <stdlib.h>

static unsigned int highest_power_of_two(unsigned int n)
{
    unsigned int result;

    if (n == 0U) {
        return 0U;
    }

    result = 1U;
    while ((n >> 1U) != 0U) {
        result <<= 1U;
        n >>= 1U;
    }

    return result;
}

int main(void)
{
    unsigned int number;
    unsigned int answer;
    int scan_result;

    printf("Enter a positive integer: ");

    scan_result = scanf("%u", &number);
    if (scan_result != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    answer = highest_power_of_two(number);

    if (answer == 0U) {
        printf("No power of 2 exists less than or equal to %u\n", number);
    } else {
        printf("Highest power of 2 less than or equal to %u is %u\n", number, answer);
    }

    return EXIT_SUCCESS;
}