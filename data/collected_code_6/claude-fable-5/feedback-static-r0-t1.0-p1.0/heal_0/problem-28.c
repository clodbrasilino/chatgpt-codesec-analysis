#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int binomial_coefficient(unsigned int n, unsigned int k, unsigned long long *result)
{
    unsigned long long res = 1ULL;
    unsigned int i;

    if (result == NULL) {
        return -1;
    }

    if (k > n) {
        *result = 0ULL;
        return 0;
    }

    if (k > n - k) {
        k = n - k;
    }

    for (i = 0U; i < k; i++) {
        if (res > ULLONG_MAX / (unsigned long long)(n - i)) {
            return -1;
        }
        res = res * (unsigned long long)(n - i);
        res = res / (unsigned long long)(i + 1U);
    }

    *result = res;
    return 0;
}

int main(void)
{
    unsigned int n = 0U;
    unsigned int k = 0U;
    unsigned long long result = 0ULL;

    printf("Enter n: ");
    if (scanf("%u", &n) != 1) {
        fprintf(stderr, "Invalid input for n\n");
        return EXIT_FAILURE;
    }

    printf("Enter k: ");
    if (scanf("%u", &k) != 1) {
        fprintf(stderr, "Invalid input for k\n");
        return EXIT_FAILURE;
    }

    if (binomial_coefficient(n, k, &result) != 0) {
        fprintf(stderr, "Computation failed due to overflow or invalid arguments\n");
        return EXIT_FAILURE;
    }

    printf("C(%u, %u) = %llu\n", n, k, result);
    return EXIT_SUCCESS;
}