#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int tetrahedral_number(uint64_t n, uint64_t *result)
{
    uint64_t factors[3] = {n, n + 1U, n + 2U};

    if (result == NULL || n > UINT64_MAX - 2U) {
        return 0;
    }

    for (size_t divisor = 2U; divisor <= 3U; ++divisor) {
        uint64_t remaining = divisor;

        for (size_t i = 0U; i < 3U && remaining > 1U; ++i) {
            const uint64_t factor = (remaining == 2U) ? 2U : 3U;

            if (factors[i] % factor == 0U) {
                factors[i] /= factor;
                remaining /= factor;
            }
        }

        if (remaining != 1U) {
            return 0;
        }
    }

    if (factors[0] != 0U && factors[1] > UINT64_MAX / factors[0]) {
        return 0;
    }

    const uint64_t partial = factors[0] * factors[1];

    if (factors[2] != 0U && partial > UINT64_MAX / factors[2]) {
        return 0;
    }

    *result = partial * factors[2];
    return 1;
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s n\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *end = NULL;
    errno = 0;
    const uintmax_t parsed = strtoumax(argv[1], &end, 10);

    if (errno != 0 || end == argv[1] || *end != '\0' || parsed > UINT64_MAX) {
        fprintf(stderr, "Invalid nonnegative integer\n");
        return EXIT_FAILURE;
    }

    uint64_t result = 0U;

    if (!tetrahedral_number((uint64_t)parsed, &result)) {
        fprintf(stderr, "Result is outside the uint64_t range\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}