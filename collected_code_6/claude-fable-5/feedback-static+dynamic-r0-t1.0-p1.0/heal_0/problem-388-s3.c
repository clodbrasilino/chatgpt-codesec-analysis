#include <stdio.h>
#include <stdlib.h>

unsigned long highest_power_of_two(unsigned long n)
{
    unsigned long result;

    if (n == 0UL) {
        return 0UL;
    }

    result = 1UL;
    while (result <= n / 2UL) {
        result *= 2UL;
    }

    return result;
}

int main(void)
{
    unsigned long n;
    unsigned long answer;
    int scanned;

    printf("Enter a non-negative integer: ");
    scanned = scanf("%lu", &n);

    if (scanned != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    answer = highest_power_of_two(n);

    if (answer == 0UL) {
        printf("There is no power of 2 less than or equal to %lu.\n", n);
    } else {
        printf("The highest power of 2 less than or equal to %lu is %lu.\n", n, answer);
    }

    return EXIT_SUCCESS;
}