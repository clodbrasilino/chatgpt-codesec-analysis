#include <stdio.h>
#include <stdlib.h>

static int sum_positive_sequence(unsigned long long n, unsigned long long *result)
{
    unsigned long long terms;

    if (result == NULL) {
        return 0;
    }

    terms = (n + 1ULL) / 2ULL;

    if ((n & 1ULL) == 0ULL) {
        *result = terms * (terms + 1ULL);
    } else {
        *result = terms * terms;
    }

    return 1;
}

int main(void)
{
    unsigned long long n;
    unsigned long long sum;

    if (scanf("%llu", &n) != 1) {
        return EXIT_FAILURE;
    }

    if (!sum_positive_sequence(n, &sum)) {
        return EXIT_FAILURE;
    }

    if (printf("%llu\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}