#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_fifth_powers_of_odds(uint64_t n, uint64_t *result)
{
    uint64_t sum = 0;

    if (result == NULL || n > 1324U) {
        return 0;
    }

    for (uint64_t i = 0; i < n; ++i) {
        const uint64_t odd = (2U * i) + 1U;
        const uint64_t square = odd * odd;
        const uint64_t fourth = square * square;
        const uint64_t fifth = fourth * odd;

        if (UINT64_MAX - sum < fifth) {
            return 0;
        }

        sum += fifth;
    }

    *result = sum;
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
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (!sum_fifth_powers_of_odds(n, &result)) {
        fprintf(stderr, "Result exceeds the supported range\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}