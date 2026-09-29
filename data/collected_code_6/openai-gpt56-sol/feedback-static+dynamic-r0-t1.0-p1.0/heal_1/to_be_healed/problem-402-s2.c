#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t add_mod(uint64_t a, uint64_t b, uint64_t p)
{
    return a >= p - b ? a - (p - b) : a + b;
}

static uint64_t mul_mod(uint64_t a, uint64_t b, uint64_t p)
{
    uint64_t result = 0;

    a %= p;
    while (b != 0) {
        if ((b & 1U) != 0U) {
            result = add_mod(result, a, p);
        }
        b >>= 1U;
        if (b != 0) {
            a = add_mod(a, a, p);
        }
    }

    return result;
}

static uint64_t ncr_mod(uint64_t n, uint64_t r, uint64_t p)
{
    uint64_t *values;
    uint64_t i;
    uint64_t j;
    uint64_t result;

    if (p == 1 || r > n) {
        return 0;
    }

    if (r > n - r) {
        r = n - r;
    }

    if (r > (SIZE_MAX / sizeof(*values)) - 1U) {
        errno = ENOMEM;
        return UINT64_MAX;
    }

    values = calloc((size_t)r + 1U, sizeof(*values));
    if (values == NULL) {
        return UINT64_MAX;
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
    uint64_t n;
    uint64_t r;
    uint64_t p;
    uint64_t result;

    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%" SCNu64 " %" SCNu64 " %" SCNu64, &n, &r, &p) != 3) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (p == 0) {
        fputs("Modulus must be nonzero\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    result = ncr_mod(n, r, p);
    if (result == UINT64_MAX && errno == ENOMEM) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}