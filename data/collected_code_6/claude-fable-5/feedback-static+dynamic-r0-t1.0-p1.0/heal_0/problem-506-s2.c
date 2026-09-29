#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int permutation_coefficient(unsigned int n, unsigned int k, unsigned long long *result)
{
    unsigned long long product;
    unsigned int i;

    if (result == NULL) {
        return -1;
    }

    if (k > n) {
        *result = 0ULL;
        return 0;
    }

    product = 1ULL;
    for (i = 0U; i < k; i++) {
        unsigned long long factor = (unsigned long long)(n - i);
        if (factor != 0ULL && product > ULLONG_MAX / factor) {
            return -1;
        }
        product *= factor;
    }

    *result = product;
    return 0;
}

int main(void)
{
    unsigned int n;
    unsigned int k;
    unsigned long long result;

    n = 10U;
    k = 2U;

    if (permutation_coefficient(n, k, &result) != 0) {
        (void)fprintf(stderr, "Error: overflow or invalid arguments\n");
        return EXIT_FAILURE;
    }

    if (printf("P(%u, %u) = %llu\n", n, k, result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}