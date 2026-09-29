#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'UINT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

static int jacobsthal(unsigned int n, uint64_t *result)
{
    uint64_t previous = 0;
    uint64_t current = 1;

    if (result == NULL) {
        return 0;
    }

    if (n == 0U) {
        *result = previous;
        return 1;
    }

    for (unsigned int i = 2U; i <= n; ++i) {
        if (previous > (UINT64_MAX - current) / 2U) {
            return 0;
        }

        const uint64_t next = current + 2U * previous;
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

    /* Possible weaknesses found:
     *  use of undeclared identifier 'UINT_MAX'
     *  'UINT_MAX' undeclared (first use in this function)
     *  each undeclared identifier is reported only once for each function it appears in
     */
    if (errno != 0 || end == argv[1] || *end != '\0' || input > UINT_MAX) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (!jacobsthal((unsigned int)input, &result)) {
        fprintf(stderr, "Result exceeds uint64_t range\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}