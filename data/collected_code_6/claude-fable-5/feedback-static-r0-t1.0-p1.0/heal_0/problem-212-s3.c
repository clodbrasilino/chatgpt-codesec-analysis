#include <stdio.h>
#include <stdlib.h>

unsigned long long fourth_power_sum(unsigned int n)
{
    unsigned long long sum = 0ULL;
    unsigned int i;

    for (i = 1U; i <= n; i++) {
        unsigned long long term = (unsigned long long)i;
        term = term * i;
        term = term * i;
        term = term * i;
        sum += term;
    }

    return sum;
}

int main(void)
{
    unsigned int n = 0U;
    int result;

    printf("Enter a positive integer n: ");
    result = scanf("%u", &n);

    if (result != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (n == 0U || n > 100000U) {
        fprintf(stderr, "Error: n must be between 1 and 100000.\n");
        return EXIT_FAILURE;
    }

    printf("Sum of fourth powers of first %u natural numbers: %llu\n",
           n, fourth_power_sum(n));

    return EXIT_SUCCESS;
}