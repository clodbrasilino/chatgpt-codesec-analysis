#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

static int calculate_difference(uint64_t n, uint64_t *result)
{
    __uint128_t sum;
    __uint128_t difference;

    if (result == NULL) {
        return 0;
    }

    sum = (__uint128_t)n * (n + 1U) / 2U;
    difference = sum * sum - sum;

    if (difference > UINT64_MAX) {
        return 0;
    }

    *result = (uint64_t)difference;
    return 1;
}

int main(void)
{
    uint64_t n;
    uint64_t difference;
    int trailing;

    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%" SCNu64, &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((trailing = getchar()) != '\n' && trailing != EOF) {
        if (trailing != ' ' && trailing != '\t' && trailing != '\r' &&
            trailing != '\v' && trailing != '\f') {
            fprintf(stderr, "Invalid input\n");
            return 1;
        }
    }

    if (!calculate_difference(n, &difference)) {
        fprintf(stderr, "Result is out of range\n");
        return 1;
    }

    printf("%" PRIu64 "\n", difference);
    return 0;
}