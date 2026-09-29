#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int calculate_difference(uint64_t n, uint64_t *result)
{
    uint64_t a = n;
    uint64_t b = n + 1U;

    if (result == NULL || n == UINT64_MAX) {
        return 0;
    }

    if ((a & 1U) == 0U) {
        a /= 2U;
    } else {
        b /= 2U;
    }

    if (a != 0U && b > UINT64_MAX / a) {
        return 0;
    }

    const uint64_t sum = a * b;

    if (sum != 0U && sum > UINT64_MAX / sum) {
        return 0;
    }

    const uint64_t cube_sum = sum * sum;
    *result = cube_sum - sum;
    return 1;
}

int main(void)
{
    uint64_t n;
    uint64_t difference;

    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%" SCNu64, &n) != 1) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!calculate_difference(n, &difference)) {
        fputs("Result is out of range\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", difference) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}