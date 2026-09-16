#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

static int sum_of_squared_binomial_coefficients(unsigned int n, uint64_t *result)
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
        return 1;
    }

    if (!sum_of_squared_binomial_coefficients(n, &result)) {
        fputs("Input is out of range\n", stderr);
        return 1;
    }

    printf("%" PRIu64 "\n", result);
    return 0;
}