#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int binomial(unsigned int n, unsigned int k, unsigned long long *result)
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
        unsigned long long numerator = (unsigned long long)(n - i);

        if (res > ULLONG_MAX / numerator) {
            return -1;
        }
        res *= numerator;
        res /= (unsigned long long)(i + 1U);
    }

    *result = res;
    return 0;
}

static int sum_of_squares_of_binomials(unsigned int n, unsigned long long *sum)
{
    unsigned int k;
    unsigned long long total = 0ULL;

    if (sum == NULL) {
        return -1;
    }

    for (k = 0U; k <= n; k++) {
        unsigned long long coeff = 0ULL;
        unsigned long long square;

        if (binomial(n, k, &coeff) != 0) {
            return -1;
        }

        if (coeff != 0ULL && coeff > ULLONG_MAX / coeff) {
            return -1;
        }
        square = coeff * coeff;

        if (total > ULLONG_MAX - square) {
            return -1;
        }
        total += square;
    }

    *sum = total;
    return 0;
}

int main(void)
{
    unsigned int n = 4U;
    unsigned long long result = 0ULL;

    if (sum_of_squares_of_binomials(n, &result) != 0) {
        if (fprintf(stderr, "Error: computation failed or overflow detected\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("Sum of squares of binomial coefficients for n = %u is %llu\n", n, result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}