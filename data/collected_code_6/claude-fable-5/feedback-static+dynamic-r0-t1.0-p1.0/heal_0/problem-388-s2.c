#include <stdio.h>
#include <stdlib.h>

static unsigned int highest_power_of_two(unsigned int n)
{
    unsigned int power = 1U;

    if (n == 0U) {
        return 0U;
    }

    while (power <= n / 2U) {
        power *= 2U;
    }

    return power;
}

int main(void)
{
    unsigned int n = 0U;
    unsigned int result = 0U;
    int scanned = 0;

    printf("Enter a positive integer: ");
    scanned = scanf("%u", &n);

    if (scanned != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (n == 0U) {
        fprintf(stderr, "Error: input must be greater than zero.\n");
        return EXIT_FAILURE;
    }

    result = highest_power_of_two(n);
    printf("Highest power of 2 <= %u is %u\n", n, result);

    return EXIT_SUCCESS;
}