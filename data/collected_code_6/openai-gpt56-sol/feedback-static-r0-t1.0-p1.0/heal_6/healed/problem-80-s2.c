#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int tetrahedral_number(uint64_t n, uint64_t *result)
{
    if (result == NULL || n > UINT64_MAX - UINT64_C(2)) {
        return 0;
    }

    uint64_t factors[3] = {
        n,
        n + UINT64_C(1),
        n + UINT64_C(2)
    };

    for (uint64_t divisor = UINT64_C(2);
         divisor <= UINT64_C(3);
         ++divisor) {
        uint64_t remaining = divisor;

        for (size_t i = 0; i < 3 && remaining > UINT64_C(1); ++i) {
            uint64_t a = factors[i];
            uint64_t b = remaining;

            while (b != 0) {
                const uint64_t remainder = a % b;
                a = b;
                b = remainder;
            }

            if (a > UINT64_C(1)) {
                factors[i] /= a;
                remaining /= a;
            }
        }

        if (remaining != UINT64_C(1)) {
            return 0;
        }
    }

    if (factors[0] != 0 &&
        factors[1] > UINT64_MAX / factors[0]) {
        return 0;
    }

    const uint64_t partial = factors[0] * factors[1];

    if (factors[2] != 0 &&
        partial > UINT64_MAX / factors[2]) {
        return 0;
    }

    *result = partial * factors[2];
    return 1;
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fputs("Usage: program n\n", stderr);
        return EXIT_FAILURE;
    }

    const char *const input = argv[1];

    if (input == NULL || input[0] == '\0' || input[0] == '-') {
        fputs("Invalid nonnegative integer\n", stderr);
        return EXIT_FAILURE;
    }

    char *end = NULL;
    errno = 0;

    const uintmax_t parsed = strtoumax(input, &end, 10);

    if (errno == ERANGE ||
        end == input ||
        end == NULL ||
        *end != '\0' ||
        parsed > UINT64_MAX) {
        fputs("Invalid nonnegative integer\n", stderr);
        return EXIT_FAILURE;
    }

    uint64_t result;

    if (!tetrahedral_number((uint64_t)parsed, &result)) {
        fputs("Result is outside the uint64_t range\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}