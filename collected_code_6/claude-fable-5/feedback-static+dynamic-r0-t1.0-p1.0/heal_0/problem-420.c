#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int cube_sum_even(unsigned int n, unsigned long long *result)
{
    unsigned long long sum = 0;
    unsigned int i;

    if (result == NULL) {
        return -1;
    }

    for (i = 1; i <= n; i++) {
        unsigned long long term = (unsigned long long)2 * i;
        unsigned long long cube;

        if (term > 2642245ULL) {
            return -1;
        }

        cube = term * term * term;

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
    unsigned int n = 0;
    unsigned long long result = 0;

    printf("Enter n: ");
    if (scanf("%u", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (cube_sum_even(n, &result) != 0) {
        fprintf(stderr, "Computation failed (overflow or invalid argument)\n");
        return EXIT_FAILURE;
    }

    printf("Cube sum of first %u even natural numbers: %llu\n", n, result);
    return EXIT_SUCCESS;
}