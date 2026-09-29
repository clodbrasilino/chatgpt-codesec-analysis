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

static int parse_input(uint32_t *n, uint32_t *k)
{
    char buffer[256];
    char *cursor;
    char *end;
    uintmax_t first;
    uintmax_t second;

    if (n == NULL || k == NULL || fgets(buffer, sizeof buffer, stdin) == NULL) {
        return 0;
    }

    cursor = buffer;
    errno = 0;
    first = strtoumax(cursor, &end, 10);
    if (cursor == end || errno == ERANGE || first > UINT32_MAX) {
        return 0;
    }

    cursor = end;
    errno = 0;
    second = strtoumax(cursor, &end, 10);
    if (cursor == end || errno == ERANGE || second > UINT32_MAX) {
        return 0;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' || *end == '\n' ||
           *end == '\v' || *end == '\f') {
        ++end;
    }

    if (*end != '\0') {
        return 0;
    }

    *n = (uint32_t)first;
    *k = (uint32_t)second;
    return 1;
}

int main(void)
{
    uint32_t n;
    uint32_t k;
    uint64_t result;

    if (printf("Enter n and k: ") < 0 || fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    if (!parse_input(&n, &k)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!binomial_coefficient(n, k, &result)) {
        fputs("Invalid arguments or arithmetic overflow\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}