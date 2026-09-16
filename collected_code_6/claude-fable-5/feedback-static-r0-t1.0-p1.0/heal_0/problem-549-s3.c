#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static unsigned long long odd_num_sum(unsigned int n, int *error)
{
    unsigned long long sum = 0ULL;
    unsigned int i;

    *error = 0;

    for (i = 1U; i <= n; i++) {
        unsigned long long odd = (2ULL * (unsigned long long)i) - 1ULL;
        unsigned long long p2 = odd * odd;
        unsigned long long p4 = p2 * p2;
        unsigned long long p5 = p4 * odd;

        if (odd != 0ULL && p2 / odd != odd) {
            *error = 1;
            return 0ULL;
        }
        if (p2 != 0ULL && p4 / p2 != p2) {
            *error = 1;
            return 0ULL;
        }
        if (p4 != 0ULL && p5 / p4 != odd) {
            *error = 1;
            return 0ULL;
        }
        if (sum > ULLONG_MAX - p5) {
            *error = 1;
            return 0ULL;
        }
        sum += p5;
    }

    return sum;
}

int main(void)
{
    unsigned int n = 0U;
    int error = 0;
    unsigned long long result;

    printf("Enter n: ");
    if (scanf("%u", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    result = odd_num_sum(n, &error);
    if (error != 0) {
        fprintf(stderr, "Overflow detected for n = %u\n", n);
        return EXIT_FAILURE;
    }

    printf("Sum of fifth powers of first %u odd natural numbers: %llu\n", n, result);
    return EXIT_SUCCESS;
}