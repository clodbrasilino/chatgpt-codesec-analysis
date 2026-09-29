#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int sum_even_index_binomials(unsigned int n, unsigned long long *result)
{
    if (result == NULL) {
        return -1;
    }

    if (n == 0U) {
        *result = 1ULL;
        return 0;
    }

    if (n - 1U >= (unsigned int)(sizeof(unsigned long long) * CHAR_BIT)) {
        return -1;
    }

    *result = 1ULL << (n - 1U);
    return 0;
}

int main(void)
{
    unsigned int n = 4U;
    unsigned long long sum = 0ULL;

    if (sum_even_index_binomials(n, &sum) != 0) {
        if (fprintf(stderr, "Error: computation failed for n = %u\n", n) < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("Sum of even index binomial coefficients for n = %u is %llu\n", n, sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}