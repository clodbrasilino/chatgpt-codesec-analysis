#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int cube_sum_even(unsigned int n, unsigned long long *result)
{
    unsigned long long sum = 0ULL;
    unsigned int i;

    if (result == NULL) {
        return -1;
    }

    for (i = 1U; i <= n; i++) {
        unsigned long long even = 2ULL * (unsigned long long)i;
        unsigned long long cube;

        if (even > 0ULL && even > ULLONG_MAX / even) {
            return -1;
        }
        cube = even * even;

        if (cube > 0ULL && even > ULLONG_MAX / cube) {
            return -1;
        }
        cube = cube * even;

        if (sum > ULLONG_MAX - cube) {
            return -1;
        }
        sum += cube;
    }

    *result = sum;
    return 0;
}

int main(void)
{
    unsigned int n = 0U;
    unsigned long long result = 0ULL;
    int scan_status;

    printf("Enter n: ");
    scan_status = scanf("%u", &n);

    if (scan_status != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (cube_sum_even(n, &result) != 0) {
        fprintf(stderr, "Computation error: overflow or invalid argument\n");
        return EXIT_FAILURE;
    }

    printf("Cube sum of first %u even natural numbers: %llu\n", n, result);
    return EXIT_SUCCESS;
}