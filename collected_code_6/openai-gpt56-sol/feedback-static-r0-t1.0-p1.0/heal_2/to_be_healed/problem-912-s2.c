#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int lobb_number(uint32_t n, uint32_t m, uint64_t *result)
{
    uint64_t value = 1;
    uint32_t k;

    if (result == NULL || n == 0 || m >= n) {
        return 0;
    }

    for (k = 1; k <= m; ++k) {
        uint64_t numerator = (uint64_t)(n - k) * (uint64_t)(n + k);
        uint64_t denominator = (uint64_t)k * (uint64_t)(k + 1);

        if (numerator != 0 && value > UINT64_MAX / numerator) {
            return 0;
        }

        value *= numerator;

        if (value % denominator != 0) {
            return 0;
        }

        value /= denominator;
    }

    *result = value;
    return 1;
}

static int parse_uint32(const char *text, uint32_t *value)
{
    char *end = NULL;
    uintmax_t parsed;

    if (text == NULL || value == NULL || *text == '\0' || *text == '-') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(text, &end, 10);

    if (errno != 0 || end == text || *end != '\0' || parsed > UINT32_MAX) {
        return 0;
    }

    *value = (uint32_t)parsed;
    return 1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    uint32_t n;
    uint32_t m;
    uint64_t result;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s n m\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (!parse_uint32(argv[1], &n) || !parse_uint32(argv[2], &m)) {
        fputs("Error: n and m must be nonnegative 32-bit integers.\n", stderr);
        return EXIT_FAILURE;
    }

    if (n == 0 || m >= n) {
        fputs("Error: require n > 0 and 0 <= m < n.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!lobb_number(n, m, &result)) {
        fputs("Error: the result cannot be represented as uint64_t.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}