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

    if (result == NULL) {
        return 0;
    }

    factors[0] = n;
    factors[1] = n + 1U;
    factors[2] = (2U * n) + 1U;
    factors[3] = (3U * n * n) + (3U * n) - 1U;
    factors[4] = 30U;

    for (i = 0U; i < 4U; ++i) {
        uint64_t divisor = factors[4];
        uint64_t factor = factors[i];
        uint64_t candidate;

        for (candidate = 2U; candidate <= divisor / candidate; ++candidate) {
            while (divisor % candidate == 0U &&
                   factor % candidate == 0U) {
                divisor /= candidate;
                factor /= candidate;
            }
        }

        if (divisor > 1U && factor % divisor == 0U) {
            factor /= divisor;
            divisor = 1U;
        }

        factors[i] = factor;
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

    while (*end == ' ' || *end == '\t' || *end == '\r' || *end == '\n' ||
           *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    n = (uint64_t)parsed;

    if (n == 0U || n > 92681U || !sum_fourth_powers(n, &result)) {
        fputs("Input is out of range\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}