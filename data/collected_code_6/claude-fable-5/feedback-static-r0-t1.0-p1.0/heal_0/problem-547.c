#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static unsigned int hamming_distance(unsigned long long a, unsigned long long b)
{
    unsigned long long x = a ^ b;
    unsigned int count = 0U;

    while (x != 0ULL) {
        count += (unsigned int)(x & 1ULL);
        x >>= 1U;
    }

    return count;
}

static int sum_consecutive_hamming(unsigned long long n, unsigned long long *result)
{
    unsigned long long total = 0ULL;
    unsigned long long i;

    if (result == NULL) {
        return -1;
    }

    for (i = 1ULL; i <= n; i++) {
        unsigned int d = hamming_distance(i - 1ULL, i);

        if (total > ULLONG_MAX - (unsigned long long)d) {
            return -1;
        }
        total += (unsigned long long)d;
    }

    *result = total;
    return 0;
}

int main(void)
{
    unsigned long long n = 0ULL;
    unsigned long long result = 0ULL;
    int scan_status;

    printf("Enter a non-negative integer n: ");
    scan_status = scanf("%llu", &n);

    if (scan_status != 1) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    if (sum_consecutive_hamming(n, &result) != 0) {
        fprintf(stderr, "Computation failed due to overflow or invalid arguments.\n");
        return EXIT_FAILURE;
    }

    printf("Sum of Hamming distances from 0 to %llu: %llu\n", n, result);

    return EXIT_SUCCESS;
}