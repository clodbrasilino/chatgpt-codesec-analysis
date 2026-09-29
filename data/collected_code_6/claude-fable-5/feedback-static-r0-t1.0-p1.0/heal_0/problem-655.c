#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int sum_of_fifth_powers(unsigned int n, unsigned long long *result)
{
    unsigned long long sum = 0ULL;
    unsigned int i;

    if (result == NULL) {
        return -1;
    }

    for (i = 1U; i <= n; i++) {
        unsigned long long value = (unsigned long long)i;
        unsigned long long power = value * value * value * value * value;

        if (sum > ULLONG_MAX - power) {
            return -1;
        }
        sum += power;
    }

    *result = sum;
    return 0;
}

int main(void)
{
    unsigned int n = 0U;
    unsigned long long result = 0ULL;

    printf("Enter a natural number: ");
    if (scanf("%u", &n) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    if (sum_of_fifth_powers(n, &result) != 0) {
        fprintf(stderr, "Computation failed due to overflow or invalid argument.\n");
        return EXIT_FAILURE;
    }

    printf("Sum of fifth powers of first %u natural numbers: %llu\n", n, result);
    return EXIT_SUCCESS;
}