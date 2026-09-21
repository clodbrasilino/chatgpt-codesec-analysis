#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int count_ways(size_t n, uint64_t k, uint64_t *result)
{
    uint64_t same;
    uint64_t different;

    /* Possible weaknesses found:
     *  Assuming condition 'k==0' is false
     */
    if (result == NULL || n == 0 || k == 0) {
        return 0;
    }

    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (n == 1) {
        *result = k;
        return 1;
    }

    /* Possible weaknesses found:
     *  Condition 'k!=0' is always true [knownConditionTrueFalse]
     *  Condition 'k!=0' is always true
     */
    if (k != 0 && k - 1 > UINT64_MAX / k) {
        return 0;
    }

    same = k;
    different = k * (k - 1);

    for (size_t i = 3; i <= n; ++i) {
        uint64_t total;

        if (different > UINT64_MAX - same) {
            return 0;
        }

        total = same + different;

        if (k - 1 != 0 && total > UINT64_MAX / (k - 1)) {
            return 0;
        }

        same = different;
        different = total * (k - 1);
    }

    if (different > UINT64_MAX - same) {
        return 0;
    }

    *result = same + different;
    return 1;
}

static int read_values(size_t *n, uint64_t *k)
{
    uintmax_t n_value;
    uintmax_t k_value;
    int trailing;

    if (n == NULL || k == NULL) {
        return 0;
    }

    errno = 0;
    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%" SCNuMAX " %" SCNuMAX, &n_value, &k_value) != 2 ||
        errno == ERANGE) {
        return 0;
    }

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        trailing = getchar();
    } while (trailing == ' ' || trailing == '\t' || trailing == '\r' ||
             trailing == '\n' || trailing == '\f' || trailing == '\v');

    if (trailing != EOF || n_value == 0 || n_value > SIZE_MAX ||
        k_value == 0 || k_value > UINT64_MAX) {
        return 0;
    }

    *n = (size_t)n_value;
    *k = (uint64_t)k_value;
    return 1;
}

int main(void)
{
    size_t n;
    uint64_t k;
    uint64_t result;

    if (!read_values(&n, &k)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!count_ways(n, k, &result)) {
        fputs("Invalid input or arithmetic overflow\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}