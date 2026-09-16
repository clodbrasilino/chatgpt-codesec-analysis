#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool permutation_coefficient(uint64_t n, uint64_t k, uint64_t *result)
{
    uint64_t value = 1;

    if (result == NULL || k > n) {
        return false;
    }

    for (uint64_t i = 0; i < k; ++i) {
        const uint64_t factor = n - i;

        if (factor != 0 && value > UINT64_MAX / factor) {
            return false;
        }

        value *= factor;
    }

    *result = value;
    return true;
}

static bool parse_uint64(const char *text, uint64_t *value)
{
    char *end = NULL;
    uintmax_t parsed;

    if (text == NULL || value == NULL || *text == '\0' || *text == '-') {
        return false;
    }

    errno = 0;
    parsed = strtoumax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed > UINT64_MAX) {
        return false;
    }

    *value = (uint64_t)parsed;
    return true;
}

int main(int argc, const char *const argv[])
{
    uint64_t n;
    uint64_t k;
    uint64_t result;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s n k\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (!parse_uint64(argv[1], &n) || !parse_uint64(argv[2], &k)) {
        fputs("Error: n and k must be nonnegative integers.\n", stderr);
        return EXIT_FAILURE;
    }

    if (k > n) {
        fputs("Error: k must not exceed n.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!permutation_coefficient(n, k, &result)) {
        fputs("Error: result exceeds the range of uint64_t.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}