#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t add_mod(uint64_t a, uint64_t b, uint64_t p)
{
    return a >= p - b ? a - (p - b) : a + b;
}

static uint64_t ncr_mod(uint64_t n, uint64_t r, uint64_t p, int *error)
{
    uint64_t *values;
    uint64_t i;
    uint64_t j;
    uint64_t result;

    *error = 0;

    if (p == 1 || r > n) {
        return 0;
    }

    if (r > n - r) {
        r = n - r;
    }

    if (r > (uint64_t)(SIZE_MAX / sizeof(*values)) - 1U) {
        *error = ENOMEM;
        return 0;
    }

    values = calloc((size_t)r + 1U, sizeof(*values));
    if (values == NULL) {
        *error = ENOMEM;
        return 0;
    }

    values[0] = 1U % p;

    for (i = 1; i <= n; ++i) {
        uint64_t limit = i < r ? i : r;

        for (j = limit; j > 0; --j) {
            values[j] = add_mod(values[j], values[j - 1U], p);
        }
    }

    result = values[r];
    free(values);
    return result;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    char extra;
    uint64_t n;
    uint64_t r;
    uint64_t p;
    uint64_t result;
    int error;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (sscanf(input,
               " %" SCNu64 " %" SCNu64 " %" SCNu64 " %c",
               &n, &r, &p, &extra) != 3) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (p == 0) {
        fputs("Modulus must be nonzero\n", stderr);
        return EXIT_FAILURE;
    }

    result = ncr_mod(n, r, p, &error);
    if (error != 0) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}