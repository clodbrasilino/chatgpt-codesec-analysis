#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'UINT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

static int delannoy_number(unsigned int n, uint64_t *result)
{
    if (result == NULL) {
        return 0;
    }

    uint64_t value = 1U;

    for (unsigned int k = 0U; k < n; ++k) {
        uint64_t multiplier = (uint64_t)(2U * k + 1U);
        uint64_t previous = (k == 0U) ? 0U : value;

        if (k == 0U) {
            value = 3U;
            continue;
        }

        uint64_t preceding = 1U;
        for (unsigned int i = 1U; i < k; ++i) {
            uint64_t next_multiplier = (uint64_t)(2U * i + 1U);

            if (value > UINT64_MAX / next_multiplier ||
                preceding > UINT64_MAX / i) {
                return 0;
            }

            uint64_t numerator = next_multiplier * value - (uint64_t)i * preceding;
            preceding = value;
            value = numerator / (i + 1U);
        }

        if (value > UINT64_MAX / multiplier ||
            previous > UINT64_MAX / k) {
            return 0;
        }

        uint64_t numerator = multiplier * value - (uint64_t)k * previous;
        value = numerator / (k + 1U);
    }

    *result = value;
    return 1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    char *end = NULL;
    unsigned long parsed = strtoul(argv[1], &end, 10);

    /* Possible weaknesses found:
     *  use of undeclared identifier 'UINT_MAX'
     *  'UINT_MAX' undeclared (first use in this function)
     *  each undeclared identifier is reported only once for each function it appears in
     */
    if (errno != 0 || end == argv[1] || *end != '\0' || parsed > UINT_MAX) {
        fprintf(stderr, "Invalid nonnegative integer\n");
        return EXIT_FAILURE;
    }

    uint64_t result = 0U;

    if (!delannoy_number((unsigned int)parsed, &result)) {
        fprintf(stderr, "Result exceeds uint64_t range\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}