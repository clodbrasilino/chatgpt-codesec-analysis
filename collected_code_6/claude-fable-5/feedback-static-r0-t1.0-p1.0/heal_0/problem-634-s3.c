#include <stdio.h>
#include <stdlib.h>

unsigned long long even_power_sum(unsigned int n)
{
    unsigned long long sum = 0ULL;
    unsigned int i;

    for (i = 1U; i <= n; i++) {
        unsigned long long term = (unsigned long long)(2U * i);
        term = term * term * term * term;
        sum += term;
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
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    if (n > 65535U) {
        fprintf(stderr, "Input too large, risk of overflow.\n");
        return EXIT_FAILURE;
    }

    printf("Sum of fourth powers of first %u even natural numbers: %llu\n",
           n, even_power_sum(n));

    return EXIT_SUCCESS;
}