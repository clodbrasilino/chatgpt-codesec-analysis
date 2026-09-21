#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

static int sum_odd_squares(uint64_t n, uint64_t *result)
{
    if (result == NULL || n > 1903309U) {
        return 0;
    }

    *result = n * (2U * n - 1U) * (2U * n + 1U) / 3U;
    return 1;
}

int main(void)
{
    uint64_t n;
    uint64_t result;
    int status;

    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    status = scanf("%" SCNu64, &n);
    if (status != 1) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!sum_odd_squares(n, &result)) {
        fputs("Input is too large\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}