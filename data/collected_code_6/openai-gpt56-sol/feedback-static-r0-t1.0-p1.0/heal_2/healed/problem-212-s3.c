#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_fourth_powers(uint64_t n, uint64_t *result)
{
    uint64_t factors[4];
    uint64_t divisor = 30;
    uint64_t value = 1;
    size_t i;

    if (result == NULL || n == 0 || n > 4934) {
        return 0;
    }

    factors[0] = n;
    factors[1] = n + 1;
    factors[2] = 2 * n + 1;
    factors[3] = 3 * n * n + 3 * n - 1;

    for (i = 0; i < 4 && divisor > 1; ++i) {
        uint64_t candidate;

        for (candidate = 2; candidate <= divisor; ++candidate) {
            while (divisor % candidate == 0 &&
                   factors[i] % candidate == 0) {
                factors[i] /= candidate;
                divisor /= candidate;
            }
        }
    }

    if (divisor != 1) {
        return 0;
    }

    for (i = 0; i < 4; ++i) {
        if (factors[i] != 0 && value > UINT64_MAX / factors[i]) {
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
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (input[0] != '\0' && input[sizeof input - 2] != '\n') {
        int ch = getchar();

        if (ch != '\n' && ch != EOF) {
            while ((ch = getchar()) != '\n' && ch != EOF) {
            }
            fputs("Invalid input\n", stderr);
            return EXIT_FAILURE;
        }
    }

    errno = 0;
    end = input;
    parsed = strtoumax(input, &end, 10);

    if (end == input || errno == ERANGE) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0' || parsed == 0 || parsed > 4934) {
        fputs("Input is out of the supported range\n", stderr);
        return EXIT_FAILURE;
    }

    n = (uint64_t)parsed;

    if (!sum_fourth_powers(n, &result)) {
        fputs("Input is out of the supported range\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Sum: %" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}