#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

static int sum_odd_squares(uint64_t n, uint64_t *result)
{
    if (result == NULL) {
        return 0;
    }

    if (n != 0U && n > UINT64_MAX / n) {
        return 0;
    }

    uint64_t n_squared = n * n;

    if (n_squared != 0U && n > UINT64_MAX / n_squared) {
        return 0;
    }

    uint64_t n_cubed = n_squared * n;

    if (n_cubed > (UINT64_MAX - n) / 4U) {
        return 0;
    }

    *result = (4U * n_cubed - n) / 3U;
    return 1;
}

int main(void)
{
    uint64_t n;
    uint64_t sum;

    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%" SCNu64, &n) != 1) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!sum_odd_squares(n, &sum)) {
        fputs("Result out of range\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", sum);
    return EXIT_SUCCESS;
}