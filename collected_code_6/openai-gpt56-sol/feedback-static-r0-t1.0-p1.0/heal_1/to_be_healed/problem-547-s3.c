#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'errno' is defined in header '<errno.h>'; this is probably fixable by adding '#include <errno.h>'
  */

static unsigned int hamming_distance(uint64_t a, uint64_t b)
{
    uint64_t value = a ^ b;
    unsigned int distance = 0U;

    while (value != 0U) {
        distance += (unsigned int)(value & UINT64_C(1));
        value >>= 1U;
    }

    return distance;
}

static int sum_consecutive_hamming_distances(uint64_t o, uint64_t n,
                                             uint64_t *result)
{
    uint64_t sum = 0U;

    if (result == NULL || o > n) {
        return 0;
    }

    for (uint64_t current = o; current < n; ++current) {
        unsigned int distance = hamming_distance(current, current + UINT64_C(1));

        if (UINT64_MAX - sum < (uint64_t)distance) {
            return 0;
        }

        sum += (uint64_t)distance;
    }

    *result = sum;
    return 1;
}

static int parse_uint64(const char *text, uint64_t *value)
{
    char *end = NULL;
    uintmax_t parsed;

    if (text == NULL || value == NULL || *text == '\0' || *text == '-') {
        return 0;
    }

    /* Possible weaknesses found:
     *  each undeclared identifier is reported only once for each function it appears in
     *  use of undeclared identifier 'errno'
     *  'errno' undeclared (first use in this function)
     */
    errno = 0;
    parsed = strtoumax(text, &end, 10);

    /* Possible weaknesses found:
     *  'ERANGE' undeclared (first use in this function)
     *  use of undeclared identifier 'errno'
     *  use of undeclared identifier 'ERANGE'
     */
    if (errno == ERANGE || end == text || *end != '\0' || parsed > UINT64_MAX) {
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
    uint64_t sum;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s o n\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (!parse_uint64(argv[1], &o) || !parse_uint64(argv[2], &n)) {
        fputs("Invalid unsigned integer input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (o > n) {
        fputs("The value of o must not exceed n.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!sum_consecutive_hamming_distances(o, n, &sum)) {
        fputs("Unable to calculate the sum.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", sum);
    return EXIT_SUCCESS;
}