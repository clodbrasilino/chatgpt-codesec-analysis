#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int count_sequences(unsigned int n, unsigned long long *result);

static int count_sequences(unsigned int n, unsigned long long *result)
{
    unsigned long long value = 1ULL;
    unsigned int i;

    if (result == NULL) {
        return -1;
    }

    for (i = 1U; i <= n; i++) {
        unsigned long long numerator = (unsigned long long)(n + i);

        if (value > ULLONG_MAX / numerator) {
            return -1;
        }

        value = value * numerator;
        value = value / (unsigned long long)i;
    }

    *result = value;
    return 0;
}

int main(void)
{
    unsigned int n = 0U;
    unsigned long long count = 0ULL;
    int scan_status;

    printf("Enter n: ");

    scan_status = scanf("%u", &n);
    if (scan_status != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (n > 30U) {
        fprintf(stderr, "Input too large\n");
        return EXIT_FAILURE;
    }

    if (count_sequences(n, &count) != 0) {
        fprintf(stderr, "Computation failed\n");
        return EXIT_FAILURE;
    }

    printf("Count of binary sequences of length %u: %llu\n", 2U * n, count);

    return EXIT_SUCCESS;
}