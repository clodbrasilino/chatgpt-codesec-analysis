#include <stdio.h>
#include <stdlib.h>

static unsigned long long odd_num_sum(unsigned int n)
{
    unsigned long long sum = 0ULL;
    unsigned int i;

    for (i = 1U; i <= n; i++) {
        unsigned long long odd = (2ULL * (unsigned long long)i) - 1ULL;
        unsigned long long fourth = odd * odd * odd * odd;
        sum += fourth;
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

    if (n > 92681U) {
        fprintf(stderr, "Input too large, result would overflow.\n");
        return EXIT_FAILURE;
    }

    printf("Sum of fourth powers of first %u odd natural numbers: %llu\n",
           n, odd_num_sum(n));

    return EXIT_SUCCESS;
}