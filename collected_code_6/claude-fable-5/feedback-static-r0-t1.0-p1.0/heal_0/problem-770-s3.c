#include <stdio.h>
#include <stdlib.h>

unsigned long long sum_of_fourth_power_of_odds(unsigned int n)
{
    unsigned long long sum = 0ULL;
    unsigned int i;

    for (i = 1U; i <= n; i++) {
        unsigned long long odd = (unsigned long long)(2U * i - 1U);
        sum += odd * odd * odd * odd;
    }

    return sum;
}

int main(void)
{
    unsigned int n = 0U;
    int result;

    printf("Enter the value of n: ");
    result = scanf("%u", &n);

    if (result != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (n > 100000U) {
        fprintf(stderr, "Error: n is too large, risk of overflow.\n");
        return EXIT_FAILURE;
    }

    printf("Sum of fourth power of first %u odd natural numbers: %llu\n",
           n, sum_of_fourth_power_of_odds(n));

    return EXIT_SUCCESS;
}