#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_of_binomial_squares(unsigned int n, uint64_t *result)
{
    uint64_t value = 1U;

    if (result == NULL || n > 33U) {
        return 0;
    }

    for (unsigned int k = 1U; k <= n; ++k) {
        value = (value * (n + k)) / k;
    }

    *result = value;
    return 1;
}

int main(void)
{
    unsigned int n;
    uint64_t result;

    if (scanf("%u", &n) != 1) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!sum_of_binomial_squares(n, &result)) {
        fputs("Input is outside the supported range\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}