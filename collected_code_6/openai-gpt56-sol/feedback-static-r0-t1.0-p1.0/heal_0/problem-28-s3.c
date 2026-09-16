#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

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
        uint64_t factor = (uint64_t)(n - k + i);

        if (value > UINT64_MAX / factor) {
            return 0;
        }

        value *= factor;
        value /= i;
    }

    *result = value;
    return 1;
}

int main(void)
{
    uint32_t n;
    uint32_t k;
    uint64_t result;

    printf("Enter n and k: ");
    if (scanf("%" SCNu32 " %" SCNu32, &n, &k) != 2) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }

    if (!binomial_coefficient(n, k, &result)) {
        fprintf(stderr, "Invalid arguments or arithmetic overflow.\n");
        return 1;
    }

    printf("%" PRIu64 "\n", result);
    return 0;
}