#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int calculate_difference(uint64_t n, uint64_t *result)
{
    uint64_t sum;
    uint64_t sum_of_squares;

    if (result == NULL || n > 77935U) {
        return 0;
    }

    sum = n * (n + 1U) / 2U;
    sum_of_squares = n * (n + 1U) * (2U * n + 1U) / 6U;
    *result = sum * sum - sum_of_squares;

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
        fputs("Input is too large\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", difference) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}