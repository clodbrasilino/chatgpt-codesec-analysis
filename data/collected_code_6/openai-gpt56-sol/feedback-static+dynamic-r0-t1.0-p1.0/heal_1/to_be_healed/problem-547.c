#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'errno' is defined in header '<errno.h>'; this is probably fixable by adding '#include <errno.h>'
  */

static uint64_t sum_consecutive_hamming_distances(uint64_t o, uint64_t n)
{
    if (o >= n) {
        return 0;
    }

    uint64_t total = 0;

    for (unsigned int k = 0; k < 64; ++k) {
        uint64_t mask = (UINT64_C(1) << (k + 1U)) - UINT64_C(1);
        uint64_t first = o | mask;

        if (first <= o) {
            continue;
        }

        if (first > n) {
            continue;
        }

        total += UINT64_C(1) + ((n - first) >> (k + 1U));
    }

    return total;
}

static int parse_uint64(const char *text, uint64_t *value)
{
    char *end = NULL;

    if (text == NULL || value == NULL || *text == '\0' || *text == '-') {
        return 0;
    }

    /* Possible weaknesses found:
     *  use of undeclared identifier 'errno'
     *  'errno' undeclared (first use in this function)
     *  each undeclared identifier is reported only once for each function it appears in
     */
    errno = 0;
    uintmax_t parsed = strtoumax(text, &end, 10);

    /* Possible weaknesses found:
     *  use of undeclared identifier 'errno'
     */
    if (errno != 0 || end == text || *end != '\0' || parsed > UINT64_MAX) {
        return 0;
    }

    *value = (uint64_t)parsed;
    return 1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    uint64_t o;
    uint64_t n;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <o> <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (!parse_uint64(argv[1], &o) || !parse_uint64(argv[2], &n) || o > n) {
        fprintf(stderr, "Invalid range\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", sum_consecutive_hamming_distances(o, n));
    return EXIT_SUCCESS;
}