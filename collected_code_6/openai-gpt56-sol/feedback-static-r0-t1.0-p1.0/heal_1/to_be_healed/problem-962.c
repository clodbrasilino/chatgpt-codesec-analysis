#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_even_naturals(uint64_t l, uint64_t r, uint64_t *result)
{
    uint64_t first;
    uint64_t last;
    uint64_t count;
    uint64_t half_count;
    uint64_t factor;

    if (result == NULL || l > r || l == 0U) {
        return 0;
    }

    first = l + (l & 1U);
    last = r - (r & 1U);

    if (first > r || last < first) {
        *result = 0U;
        return 1;
    }

    count = ((last - first) / 2U) + 1U;
    half_count = count / 2U;
    factor = first + last;

    if ((count & 1U) != 0U) {
        factor /= 2U;
    }

    if (half_count != 0U && factor > UINT64_MAX / half_count) {
        return 0;
    }

    *result = half_count * factor;
    return 1;
}

int main(void)
{
    uint64_t l;
    uint64_t r;
    uint64_t sum;
    int trailing;

    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%" SCNu64 " %" SCNu64, &l, &r) != 2) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        trailing = getchar();
    } while (trailing != '\n' && trailing != EOF && trailing == ' ');

    if (trailing != '\n' && trailing != EOF) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!sum_even_naturals(l, r, &sum)) {
        fputs("Invalid range or arithmetic overflow\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}