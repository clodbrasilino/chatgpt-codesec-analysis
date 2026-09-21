#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_fifth_powers_even(uint64_t n, uint64_t *result)
{
    uint64_t sum = 0;

    if (result == NULL) {
        return 0;
    }

    for (uint64_t i = 1; i <= n; ++i) {
        uint64_t value;

        if (i > UINT64_MAX / 2U) {
            return 0;
        }

        value = i * 2U;

        if (value != 0U &&
            (value > UINT64_MAX / value ||
             value * value > UINT64_MAX / value ||
             value * value * value > UINT64_MAX / value ||
             value * value * value * value > UINT64_MAX / value)) {
            return 0;
        }

        value = value * value * value * value * value;

        if (sum > UINT64_MAX - value) {
            return 0;
        }

        sum += value;
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
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!sum_fifth_powers_even(n, &result)) {
        fputs("Arithmetic overflow\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}