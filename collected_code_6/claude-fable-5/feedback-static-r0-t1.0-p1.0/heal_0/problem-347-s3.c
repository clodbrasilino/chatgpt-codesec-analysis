#include <stdio.h>
#include <stdlib.h>

static unsigned long long count_squares(unsigned int m, unsigned int n)
{
    unsigned long long total = 0ULL;
    unsigned int limit = (m < n) ? m : n;
    unsigned int k;

    for (k = 1; k <= limit; k++) {
        total += (unsigned long long)(m - k + 1U) * (unsigned long long)(n - k + 1U);
    }

    return total;
}

int main(void)
{
    unsigned int m = 0U;
    unsigned int n = 0U;
    int result;

    printf("Enter rectangle dimensions (m n): ");

    result = scanf("%u %u", &m, &n);
    if (result != 2) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (m == 0U || n == 0U) {
        fprintf(stderr, "Error: dimensions must be positive.\n");
        return EXIT_FAILURE;
    }

    if (m > 100000U || n > 100000U) {
        fprintf(stderr, "Error: dimensions too large.\n");
        return EXIT_FAILURE;
    }

    printf("Number of squares in a %ux%u rectangle: %llu\n", m, n, count_squares(m, n));

    return EXIT_SUCCESS;
}