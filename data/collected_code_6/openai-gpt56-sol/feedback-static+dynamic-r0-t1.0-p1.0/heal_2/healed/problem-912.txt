#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int lobb_number(uint32_t n, uint32_t m, uint64_t *result)
{
    uint64_t value = 1;

    if (result == NULL || m > n) {
        return -1;
    }

    for (uint32_t k = 1; k <= m; ++k) {
        __uint128_t numerator =
            (__uint128_t)value * ((uint64_t)n + (uint64_t)k);
        const uint64_t denominator = k;

        if (numerator % denominator != 0) {
            return -1;
        }

        numerator /= denominator;

        if (numerator > UINT64_MAX) {
            return -1;
        }

        value = (uint64_t)numerator;
    }

    {
        __uint128_t scaled =
            (__uint128_t)value * ((uint64_t)n - (uint64_t)m + UINT64_C(1));
        const uint64_t denominator = (uint64_t)n + UINT64_C(1);

        if (scaled % denominator != 0) {
            return -1;
        }

        scaled /= denominator;

        if (scaled > UINT64_MAX) {
            return -1;
        }

        *result = (uint64_t)scaled;
    }

    return 0;
}

static int parse_uint32(const char *text, uint32_t *value)
{
    char *end = NULL;
    uintmax_t parsed;

    if (text == NULL || value == NULL || *text == '\0' || *text == '-') {
        return -1;
    }

    errno = 0;
    parsed = strtoumax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed > UINT32_MAX) {
        return -1;
    }

    *value = (uint32_t)parsed;
    return 0;
}

int main(int argc, const char *const argv[])
{
    uint32_t n;
    uint32_t m;
    uint64_t result;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s n m\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (parse_uint32(argv[1], &n) != 0 ||
        parse_uint32(argv[2], &m) != 0 ||
        m > n) {
        fputs("Invalid input: require 0 <= m <= n.\n", stderr);
        return EXIT_FAILURE;
    }

    if (lobb_number(n, m, &result) != 0) {
        fputs("The Lobb number cannot be represented as uint64_t.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}