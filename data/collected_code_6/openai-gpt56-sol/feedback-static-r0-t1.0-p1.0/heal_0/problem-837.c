#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int cube_sum_first_n_odds(uint64_t n, uint64_t *result)
{
    uint64_t n_squared;

    if (result == NULL) {
        return 0;
    }

    if (n > UINT64_C(77935)) {
        return 0;
    }

    n_squared = n * n;
    *result = n_squared * (UINT64_C(2) * n_squared - UINT64_C(1));
    return 1;
}

int main(void)
{
    uint64_t n;
    uint64_t result;

    if (scanf("%" SCNu64, &n) != 1) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!cube_sum_first_n_odds(n, &result)) {
        fputs("Input is too large\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}