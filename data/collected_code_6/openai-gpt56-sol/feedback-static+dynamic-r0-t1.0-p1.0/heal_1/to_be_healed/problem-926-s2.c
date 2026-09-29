#include <errno.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'UINT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

static int rencontres(unsigned int n, uint64_t *result)
{
    uint64_t previous = 1;
    uint64_t current = 0;

    if (result == NULL) {
        return 0;
    }

    if (n == 0U) {
        *result = previous;
        return 1;
    }

    for (unsigned int i = 2U; i <= n; ++i) {
        uint64_t sum;
        uint64_t factor = (uint64_t)(i - 1U);
        uint64_t next;

        if (UINT64_MAX - current < previous) {
            return 0;
        }

        sum = current + previous;

        if (factor != 0U && sum > UINT64_MAX / factor) {
            return 0;
        }

        next = factor * sum;
        previous = current;
        current = next;
    }

    *result = current;
    return 1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    char *end = NULL;
    unsigned long input;
    uint64_t result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <nonnegative integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    input = strtoul(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        /* Possible weaknesses found:
         *  use of undeclared identifier 'UINT_MAX'
         *  'UINT_MAX' undeclared (first use in this function)
         *  each undeclared identifier is reported only once for each function it appears in
         */
        input > (unsigned long)UINT_MAX) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (!rencontres((unsigned int)input, &result)) {
        fprintf(stderr, "Result exceeds uint64_t range\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}