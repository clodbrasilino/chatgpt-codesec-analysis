#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

static int sum_fifth_powers_of_odds(uint64_t n, uint64_t *result)
{
    uint64_t sum = 0;

    if (result == NULL) {
        return 0;
    }

    for (uint64_t i = 0; i < n; ++i) {
        uint64_t odd = (2U * i) + 1U;
        uint64_t square;
        uint64_t fourth;
        uint64_t fifth;

        if (__builtin_mul_overflow(odd, odd, &square) ||
            __builtin_mul_overflow(square, square, &fourth) ||
            __builtin_mul_overflow(fourth, odd, &fifth) ||
            __builtin_add_overflow(sum, fifth, &sum)) {
            return 0;
        }
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
        return 1;
    }

    if (!sum_fifth_powers_of_odds(n, &result)) {
        fputs("Arithmetic overflow\n", stderr);
        return 1;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return 1;
    }

    return 0;
}