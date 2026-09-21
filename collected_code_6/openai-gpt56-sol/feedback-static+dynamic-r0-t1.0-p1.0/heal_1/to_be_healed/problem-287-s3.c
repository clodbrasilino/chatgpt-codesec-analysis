#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

static int sum_even_squares(uint64_t n, uint64_t *result)
{
    uint64_t a = n;
    uint64_t b = n + 1U;
    uint64_t c;
    uint64_t product;

    if (result == NULL || n > UINT64_MAX / 2U) {
        return 0;
    }

    c = (2U * n) + 1U;

    if ((a & 1U) == 0U) {
        a /= 2U;
    } else {
        b /= 2U;
    }

    if (a % 3U == 0U) {
        a /= 3U;
    } else if (b % 3U == 0U) {
        b /= 3U;
    } else {
        c /= 3U;
    }

    if (a != 0U && b > UINT64_MAX / a) {
        return 0;
    }

    product = a * b;

    if (product != 0U && c > UINT64_MAX / product) {
        return 0;
    }

    product *= c;

    if (product > UINT64_MAX / 4U) {
        return 0;
    }

    *result = 4U * product;
    return 1;
}

int main(void)
{
    uint64_t n;
    uint64_t sum;
    int trailing;

    if (printf("Enter n: ") < 0) {
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%" SCNu64, &n) != 1) {
        (void)fprintf(stderr, "Invalid input\n");
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    trailing = getchar();
    while (trailing != '\n' && trailing != EOF) {
        if (trailing != ' ' && trailing != '\t' &&
            trailing != '\r' && trailing != '\f' &&
            trailing != '\v') {
            (void)fprintf(stderr, "Invalid input\n");
            return 1;
        }
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        trailing = getchar();
    }

    if (!sum_even_squares(n, &sum)) {
        (void)fprintf(stderr, "Result exceeds the supported range\n");
        return 1;
    }

    if (printf("%" PRIu64 "\n", sum) < 0) {
        return 1;
    }

    return 0;
}