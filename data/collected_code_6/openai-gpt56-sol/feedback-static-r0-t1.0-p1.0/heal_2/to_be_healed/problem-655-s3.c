#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_fifth_powers(uint64_t n, uint64_t *result)
{
    __uint128_t value;
    __uint128_t square;

    if (result == NULL) {
        return 0;
    }

    value = (__uint128_t)n * ((__uint128_t)n + 1U);
    square = value * value;
    value = square *
            (2U * (__uint128_t)n * n + 2U * (__uint128_t)n - 1U) /
            12U;

    if (value > UINT64_MAX) {
        return 0;
    }

    *result = (uint64_t)value;
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

    if (errno == ERANGE || end == input || parsed > UINT64_MAX) {
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

    if (!sum_fifth_powers(n, &result)) {
        fputs("Result out of range\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}