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
    uint64_t result;
    uint64_t i;
    uint64_t j;
    size_t count;

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

    count = (size_t)r + 1U;
    values = calloc(count, sizeof(*values));
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
    uint64_t n;
    uint64_t r;
    uint64_t p;
    uint64_t result;
    int error;
    int conversion;
    int ch;

    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    conversion = scanf("%" SCNu64 " %" SCNu64 " %" SCNu64, &n, &r, &p);
    if (conversion != 3) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
    } while (ch == ' ' || ch == '\t' || ch == '\r');

    if (ch != '\n' && ch != EOF) {
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