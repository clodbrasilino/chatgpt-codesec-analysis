#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int sum_of_cubes(unsigned int n, unsigned long long *result)
{
    unsigned long long sum = 0ULL;
    unsigned int i;

    if (result == NULL) {
        return -1;
    }

    for (i = 1U; i <= n; i++) {
        unsigned long long cube;
        unsigned long long term = (unsigned long long)i;

        if (term > ULLONG_MAX / term) {
            return -1;
        }
        cube = term * term;

        if (cube > ULLONG_MAX / term) {
            return -1;
        }
        cube = cube * term;

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

    printf("Enter n: ");
    if (scanf("%u", &n) != 1) {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    if (sum_of_cubes(n, &result) != 0) {
        fprintf(stderr, "Error: computation failed or overflow occurred\n");
        return EXIT_FAILURE;
    }

    printf("Sum of series: %llu\n", result);
    return EXIT_SUCCESS;
}