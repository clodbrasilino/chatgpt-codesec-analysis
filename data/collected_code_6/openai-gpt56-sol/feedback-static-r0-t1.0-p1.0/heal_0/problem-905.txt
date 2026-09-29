#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_of_squared_binomial_coefficients(unsigned int n, uint64_t *result)
{
    uint64_t value = 1;

    if (result == NULL || n > 33U) {
        return 0;
    }

    for (unsigned int k = 1; k <= n; ++k) {
        const uint64_t factor = (uint64_t)n + k;
        const uint64_t divisor = k;

        if (value > UINT64_MAX / factor) {
            return 0;
        }

        value = (value * factor) / divisor;
    }

    *result = value;
    return 1;
}

int main(void)
{
    unsigned int n;
    uint64_t result;

    if (printf("Enter n: ") < 0) {
        return EXIT_FAILURE;
    }

    if (scanf("%u", &n) != 1) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!sum_of_squared_binomial_coefficients(n, &result)) {
        fputs("Result exceeds the supported range.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Sum of squares: %" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}