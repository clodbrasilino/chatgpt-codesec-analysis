#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_fifth_powers_of_odds(uint64_t n, uint64_t *result)
{
    uint64_t sum = 0;

    if (result == NULL) {
        return 0;
    }

    for (uint64_t i = 0; i < n; ++i) {
        uint64_t odd;
        uint64_t square;
        uint64_t fourth;
        uint64_t fifth;

        if (__builtin_mul_overflow(i, UINT64_C(2), &odd) ||
            __builtin_add_overflow(odd, UINT64_C(1), &odd) ||
            __builtin_mul_overflow(odd, odd, &square) ||
            __builtin_mul_overflow(square, square, &fourth) ||
            __builtin_mul_overflow(fourth, odd, &fifth) ||
            __builtin_add_overflow(sum, fifth, &sum)) {
            return 0;
        }
    }

    *result = sum;
    return 1;
}

int main(void)
{
    char input[128];
    char *end;
    uintmax_t parsed;
    uint64_t n;
    uint64_t result;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    errno = 0;
    end = input;
    parsed = strtoumax(input, &end, 10);

    if (end == input || errno == ERANGE || parsed > UINT64_MAX) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' || *end == '\n' ||
           *end == '\v' || *end == '\f') {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    n = (uint64_t)parsed;

    if (!sum_fifth_powers_of_odds(n, &result)) {
        fputs("Arithmetic overflow\n", stderr);
        return 1;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return 1;
    }

    return 0;
}