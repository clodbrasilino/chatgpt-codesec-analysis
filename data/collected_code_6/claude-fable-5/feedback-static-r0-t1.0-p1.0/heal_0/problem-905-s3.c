#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int binomial(unsigned int n, unsigned int k, unsigned long long *result)
{
    unsigned long long res = 1ULL;
    unsigned int i;

    if (k > n) {
        *result = 0ULL;
        return 0;
    }

    if (k > n - k) {
        k = n - k;
    }

    for (i = 1U; i <= k; i++) {
        if (res > ULLONG_MAX / (unsigned long long)(n - k + i)) {
            return -1;
        }
        res = res * (unsigned long long)(n - k + i);
        res = res / (unsigned long long)i;
    }

    *result = res;
    return 0;
}

static int sum_of_squares_of_binomials(unsigned int n, unsigned long long *sum)
{
    if (n > (UINT_MAX / 2U)) {
        return -1;
    }

    return binomial(2U * n, n, sum);
}

int main(void)
{
    unsigned int n = 0U;
    unsigned long long result = 0ULL;
    int status;

    printf("Enter n: ");

    if (scanf("%u", &n) != 1) {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    status = sum_of_squares_of_binomials(n, &result);

    if (status != 0) {
        fprintf(stderr, "Error: computation overflow for n = %u\n", n);
        return EXIT_FAILURE;
    }

    printf("Sum of squares of binomial coefficients for n = %u is %llu\n", n, result);

    return EXIT_SUCCESS;
}