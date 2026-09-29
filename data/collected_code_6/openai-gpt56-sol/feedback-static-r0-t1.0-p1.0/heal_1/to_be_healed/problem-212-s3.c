#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_fourth_powers(uint64_t n, uint64_t *result)
{
    uint64_t factors[5] = {n, n + 1U, 2U * n + 1U, 3U * n * n + 3U * n - 1U, 30U};
    uint64_t value = 1U;
    size_t i;

    for (i = 0U; i < 4U; ++i) {
        uint64_t divisor = factors[4];

        while (divisor > 1U) {
            uint64_t candidate;

            for (candidate = 2U; candidate <= divisor; ++candidate) {
                if (divisor % candidate == 0U && factors[i] % candidate == 0U) {
                    factors[i] /= candidate;
                    divisor /= candidate;
                    break;
                }
            }

            if (candidate > divisor) {
                break;
            }
        }

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
    int trailing;

    if (printf("Enter n: ") < 0) {
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%" SCNu64, &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        trailing = getchar();
    } while (trailing == ' ' || trailing == '\t' || trailing == '\n');

    if (trailing != EOF) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (n == 0U || n > 4934U || !sum_fourth_powers(n, &result)) {
        fprintf(stderr, "Input is out of the supported range\n");
        return EXIT_FAILURE;
    }

    if (printf("Sum: %" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}