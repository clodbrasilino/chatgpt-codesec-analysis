#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int binomial_coefficient(uint32_t n, uint32_t k, uint64_t *result)
{
    uint64_t value = 1;

    if (result == NULL || k > n) {
        return 0;
    }

    if (k > n - k) {
        k = n - k;
    }

    for (uint32_t i = 1; i <= k; ++i) {
        uint64_t factor = (uint64_t)(n - k + i);

        if (value > UINT64_MAX / factor) {
            return 0;
        }

        value = (value * factor) / i;
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
    char *cursor;
    char *end;
    uintmax_t n_value;
    uintmax_t k_value;
    uint32_t n;
    uint32_t k;
    uint64_t result;

    if (printf("Enter n and k: ") < 0) {
        return 1;
    }

    if (fflush(stdout) == EOF || fgets(input, sizeof input, stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    cursor = input;
    errno = 0;
    n_value = strtoumax(cursor, &end, 10);
    if (cursor == end || errno == ERANGE || n_value > UINT32_MAX) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    cursor = end;
    errno = 0;
    k_value = strtoumax(cursor, &end, 10);
    if (cursor == end || errno == ERANGE || k_value > UINT32_MAX) {
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

    n = (uint32_t)n_value;
    k = (uint32_t)k_value;

    if (!binomial_coefficient(n, k, &result)) {
        fputs("Invalid arguments or arithmetic overflow\n", stderr);
        return 1;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return 1;
    }

    return 0;
}