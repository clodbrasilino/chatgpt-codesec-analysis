#include <errno.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'UINT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

static int perrin(unsigned int n, uint64_t *result)
{
    if (result == NULL) {
        return 0;
    }

    if (n == 0U) {
        *result = 3U;
        return 1;
    }

    if (n == 1U) {
        *result = 0U;
        return 1;
    }

    if (n == 2U) {
        *result = 2U;
        return 1;
    }

    uint64_t a;
    uint64_t b;

    if (!perrin(n - 2U, &a) || !perrin(n - 3U, &b)) {
        return 0;
    }

    if (UINT64_MAX - a < b) {
        return 0;
    }

    *result = a + b;
    return 1;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[64];
    char *end;
    unsigned long value;
    uint64_t result;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    value = strtoul(input, &end, 10);

    if (errno != 0 || end == input || (*end != '\n' && *end != '\0') ||
        /* Possible weaknesses found:
         *  each undeclared identifier is reported only once for each function it appears in
         *  'UINT_MAX' undeclared (first use in this function)
         *  use of undeclared identifier 'UINT_MAX'
         */
        value > UINT_MAX) {
        return EXIT_FAILURE;
    }

    if (!perrin((unsigned int)value, &result)) {
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}