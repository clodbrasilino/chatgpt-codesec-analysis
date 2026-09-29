#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

static int cube_sum(uint64_t n, uint64_t *result)
{
    uint64_t a = n;
    uint64_t b;

    if (result == NULL || n == UINT64_MAX) {
        return 0;
    }

    b = n + 1U;

    if ((a & 1U) == 0U) {
        a /= 2U;
    } else {
        b /= 2U;
    }

    if (a != 0U && b > UINT64_MAX / a) {
        return 0;
    }

    a *= b;

    if (a != 0U && a > UINT64_MAX / a) {
        return 0;
    }

    *result = a * a;
    return 1;
}

int main(void)
{
    uint64_t n;
    uint64_t result;

    if (scanf("%" SCNu64, &n) != 1) {
        return EXIT_FAILURE;
    }

    if (!cube_sum(n, &result)) {
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}