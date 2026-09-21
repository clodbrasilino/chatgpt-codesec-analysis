#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_fourth_powers(uint64_t n, uint64_t *result)
{
    uint64_t factors[5] = {n, n + 1U, (2U * n) + 1U, (3U * n * n) + (3U * n) - 1U, 30U};
    uint64_t value = 1U;
    size_t i;

    for (i = 0U; i < 4U; ++i) {
        uint64_t divisor = factors[4];
        uint64_t a = factors[i];

        while (divisor != 0U && a % divisor == 0U) {
            a /= divisor;
            divisor = 1U;
        }

        if (divisor > 1U) {
            uint64_t j;
            for (j = 2U; j <= divisor; ++j) {
                while (divisor % j == 0U && a % j == 0U) {
                    divisor /= j;
                    a /= j;
                }
            }
        }

        factors[i] = a;
        factors[4] = divisor;
    }

    if (factors[4] != 1U) {
        return 0;
    }

    for (i = 0U; i < 4U; ++i) {
        if (factors[i] != 0U && value > UINT64_MAX / factors[i]) {
            return 0;
        }
        value *= factors[i];
    }

    *result = value;
    return 1;
}

int main(void)
{
    uint64_t n;
    uint64_t result;

    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%" SCNu64, &n) != 1) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (n == 0U || n > 92681U || !sum_fourth_powers(n, &result)) {
        fputs("Input is out of range\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}