#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int binomial_coefficient(uint32_t n, uint32_t k, uint64_t *result)
{
    uint64_t value = 1;

    if (result == NULL || k > n) {
        return 0;
    }

    if (k > n - k) {
        k = n - k;
    }

    for (uint32_t i = 1; i <= k; ++i) {
        const uint64_t factor = (uint64_t)(n - k + i);

        if (value > UINT64_MAX / factor) {
            return 0;
        }

        value = (value * factor) / i;
    }

    *result = value;
    return 1;
}

int main(void)
{
    uint32_t n;
    uint32_t k;
    uint64_t result;

    if (scanf("%" SCNu32 " %" SCNu32, &n, &k) != 2) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!binomial_coefficient(n, k, &result)) {
        fputs("Invalid arguments or arithmetic overflow\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}