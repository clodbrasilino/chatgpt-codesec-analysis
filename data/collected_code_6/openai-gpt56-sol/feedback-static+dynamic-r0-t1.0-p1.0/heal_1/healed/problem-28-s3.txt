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

        value *= factor;
        value /= i;
    }

    *result = value;
    return 1;
}

static int read_values(uint32_t *n, uint32_t *k)
{
    char buffer[128];
    char *end;
    uintmax_t first;
    uintmax_t second;

    if (n == NULL || k == NULL || fgets(buffer, sizeof buffer, stdin) == NULL) {
        return 0;
    }

    errno = 0;
    first = strtoumax(buffer, &end, 10);
    if (errno == ERANGE || end == buffer || first > UINT32_MAX) {
        return 0;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end == '\0' || *end == '-') {
        return 0;
    }

    char *second_start = end;

    errno = 0;
    second = strtoumax(second_start, &end, 10);
    if (errno == ERANGE || end == second_start || second > UINT32_MAX) {
        return 0;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
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

    printf("Enter n and k: ");
    fflush(stdout);

    if (!read_values(&n, &k)) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    if (!binomial_coefficient(n, k, &result)) {
        fprintf(stderr, "Invalid arguments or arithmetic overflow.\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}