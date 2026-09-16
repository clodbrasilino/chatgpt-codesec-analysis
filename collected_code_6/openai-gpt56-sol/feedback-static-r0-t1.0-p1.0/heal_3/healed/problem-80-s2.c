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
            const uint64_t common =
                factors[i] % remaining == 0
                    ? remaining
                    : remaining % factors[i] == 0
                          ? factors[i]
                          : UINT64_C(1);

            if (common > UINT64_C(1)) {
                factors[i] /= common;
                remaining /= common;
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

int main(int argc, char *const argv[const])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s n\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *const input = argv[1];
    char *end = NULL;
    errno = 0;

    const uintmax_t parsed = strtoumax(input, &end, 10);

    if (errno == ERANGE ||
        end == input ||
        *end != '\0' ||
        input[0] == '-' ||
        parsed > UINT64_MAX) {
        fprintf(stderr, "Invalid nonnegative integer\n");
        return EXIT_FAILURE;
    }

    uint64_t result;

    if (!tetrahedral_number((uint64_t)parsed, &result)) {
        fprintf(stderr, "Result is outside the uint64_t range\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}