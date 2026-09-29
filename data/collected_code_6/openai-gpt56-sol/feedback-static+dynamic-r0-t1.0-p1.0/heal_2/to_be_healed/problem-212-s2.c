#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_fourth_powers(uint64_t n, uint64_t *result)
{
    uint64_t factors[5] = {
        n,
        n + UINT64_C(1),
        (UINT64_C(2) * n) + UINT64_C(1),
        (UINT64_C(3) * n * n) + (UINT64_C(3) * n) - UINT64_C(1),
        UINT64_C(30)
    };
    uint64_t value = UINT64_C(1);
    size_t i;

    if (result == NULL) {
        return 0;
    }

    for (i = 0; i < 4; ++i) {
        uint64_t divisor = factors[4];
        uint64_t factor = factors[i];
        uint64_t candidate;

        for (candidate = UINT64_C(2); candidate <= divisor; ++candidate) {
            while (divisor % candidate == 0 && factor % candidate == 0) {
                divisor /= candidate;
                factor /= candidate;
            }
        }

        factors[i] = factor;
        factors[4] = divisor;
    }

    if (factors[4] != UINT64_C(1)) {
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[128];
    char *end;
    uintmax_t parsed;
    uint64_t n;
    uint64_t result;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = input;
    parsed = strtoumax(input, &end, 10);

    if (end == input || errno == ERANGE || parsed > UINT64_MAX) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    n = (uint64_t)parsed;

    if (n == 0 || n > UINT64_C(92681) ||
        !sum_fourth_powers(n, &result)) {
        fputs("Input is out of range\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}