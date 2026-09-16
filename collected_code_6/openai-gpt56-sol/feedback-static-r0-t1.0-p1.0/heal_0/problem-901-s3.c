#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t gcd_u64(uint64_t a, uint64_t b)
{
    while (b != 0U) {
        const uint64_t remainder = a % b;
        a = b;
        b = remainder;
    }

    return a;
}

static int smallest_multiple(uint64_t n, uint64_t *result)
{
    uint64_t value = 1U;

    if (result == NULL || n == 0U) {
        return 0;
    }

    for (uint64_t i = 2U; i <= n; ++i) {
        const uint64_t factor = i / gcd_u64(value, i);

        if (value > UINT64_MAX / factor) {
            return 0;
        }

        value *= factor;
    }

    *result = value;
    return 1;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    uintmax_t parsed;
    uint64_t result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <positive integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    parsed = strtoumax(argv[1], &end, 10);

    if (argv[1][0] == '\0' || end == argv[1] || *end != '\0' ||
        parsed == 0U || parsed > UINT64_MAX) {
        fprintf(stderr, "Invalid positive integer\n");
        return EXIT_FAILURE;
    }

    if (!smallest_multiple((uint64_t)parsed, &result)) {
        fprintf(stderr, "Result exceeds the uint64_t range\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}