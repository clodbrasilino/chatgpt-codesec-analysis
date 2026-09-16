#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'UINT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

static int nth_delannoy(unsigned int n, uint64_t *result)
{
    uint64_t value = 1;

    if (result == NULL) {
        return 0;
    }

    for (unsigned int k = 0; k < n; ++k) {
        uint64_t factor = (uint64_t)(6U * k) + 3U;
        uint64_t adjustment = k == 0U ? 0U : (uint64_t)k;
        uint64_t previous = k == 0U ? 0U : *result;

        if (value > (UINT64_MAX - adjustment * previous) / factor) {
            return 0;
        }

        *result = value;
        value = factor * value - adjustment * previous;
        value /= (uint64_t)k + 1U;
    }

    *result = value;
    return 1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    char *end = NULL;
    unsigned long input;
    uint64_t result = 0;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s n\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    input = strtoul(argv[1], &end, 10);

    /* Possible weaknesses found:
     *  each undeclared identifier is reported only once for each function it appears in
     *  use of undeclared identifier 'UINT_MAX'
     *  'UINT_MAX' undeclared (first use in this function)
     */
    if (errno != 0 || end == argv[1] || *end != '\0' || input > UINT_MAX) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (!nth_delannoy((unsigned int)input, &result)) {
        fprintf(stderr, "Result exceeds uint64_t range\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}