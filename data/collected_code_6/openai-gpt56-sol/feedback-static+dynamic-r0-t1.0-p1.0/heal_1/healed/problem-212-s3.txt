#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_fourth_powers(uint64_t n, uint64_t *result)
{
    uint64_t factors[5];
    uint64_t value = 1U;
    size_t i;

    factors[0] = n;
    factors[1] = n + 1U;
    factors[2] = 2U * n + 1U;
    factors[3] = 3U * n * n + 3U * n - 1U;
    factors[4] = 30U;

    for (i = 0U; i < 4U; ++i) {
        uint64_t divisor = factors[4];
        uint64_t candidate = 2U;

        while (divisor > 1U && candidate <= divisor) {
            if (divisor % candidate == 0U &&
                factors[i] % candidate == 0U) {
                factors[i] /= candidate;
                divisor /= candidate;
            } else {
                ++candidate;
            }
        }

        factors[4] = divisor;
    }

    if (factors[4] != 1U) {
        return 0;
    }

    for (i = 0U; i < 4U; ++i) {
        if (factors[i] != 0U && value > UINT64_MAX / factors[i]) {
            return 0;
        }
        value *= factors[i];
    }

    *result = value;
    return 1;
}

int main(void)
{
    char input[128];
    char *end;
    uintmax_t parsed;
    uint64_t n;
    uint64_t result;

    if (printf("Enter n: ") < 0) {
        return EXIT_FAILURE;
    }

    if (fgets(input, sizeof input, stdin) == NULL) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    end = input;
    parsed = strtoumax(input, &end, 10);

    if (end == input || errno == ERANGE || parsed > UINT64_MAX) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r') {
        ++end;
    }

    if (*end != '\n' && *end != '\0') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (*end == '\0') {
        int ch = getchar();

        if (ch != EOF) {
            fprintf(stderr, "Invalid input\n");
            return EXIT_FAILURE;
        }
    }

    n = (uint64_t)parsed;

    if (n == 0U || n > 4934U || !sum_fourth_powers(n, &result)) {
        fprintf(stderr, "Input is out of the supported range\n");
        return EXIT_FAILURE;
    }

    if (printf("Sum: %" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}