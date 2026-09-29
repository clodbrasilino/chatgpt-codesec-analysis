#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool gcd_u64(uint64_t a, uint64_t b, uint64_t *result)
{
    if (result == NULL) {
        return false;
    }

    while (b != 0U) {
        const uint64_t remainder = a % b;
        a = b;
        b = remainder;
    }

    *result = a;
    return true;
}

static bool catalan_number(unsigned int n, uint64_t *result)
{
    uint64_t value = 1U;

    if (result == NULL) {
        return false;
    }

    for (unsigned int i = 0U; i < n; ++i) {
        uint64_t numerator = (2U * (uint64_t)i) + 1U;
        uint64_t denominator = (uint64_t)i + 2U;
        uint64_t divisor;

        if (!gcd_u64(numerator, denominator, &divisor)) {
            return false;
        }

        numerator /= divisor;
        denominator /= divisor;

        if (!gcd_u64(value, denominator, &divisor)) {
            return false;
        }

        value /= divisor;
        denominator /= divisor;

        if (denominator != 1U || value > UINT64_MAX / numerator) {
            return false;
        }

        value *= numerator;
        if (value > UINT64_MAX / 2U) {
            return false;
        }

        value *= 2U;
    }

    *result = value;
    return true;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    unsigned long input;
    uint64_t result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s n\n", argv[0]);
        return EXIT_FAILURE;
    }

    input = strtoul(argv[1], &end, 10);
    if (argv[1][0] == '\0' || end == NULL || *end != '\0' || input > UINT_MAX) {
        fputs("Invalid nonnegative integer\n", stderr);
        return EXIT_FAILURE;
    }

    if (!catalan_number((unsigned int)input, &result)) {
        fputs("Catalan number exceeds uint64_t range\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}