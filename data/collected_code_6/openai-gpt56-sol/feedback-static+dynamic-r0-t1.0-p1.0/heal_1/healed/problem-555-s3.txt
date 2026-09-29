#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int calculate_difference(uint64_t n, uint64_t *result)
{
    __uint128_t sum;
    __uint128_t difference;

    if (result == NULL) {
        return 0;
    }

    sum = (__uint128_t)n * ((__uint128_t)n + 1U) / 2U;
    difference = sum * sum - sum;

    if (difference > UINT64_MAX) {
        return 0;
    }

    *result = (uint64_t)difference;
    return 1;
}

int main(void)
{
    char buffer[128];
    char *end;
    uintmax_t value;
    uint64_t difference;

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    errno = 0;
    value = strtoumax(buffer, &end, 10);

    if (end == buffer || errno == ERANGE || value > UINT64_MAX) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\v' || *end == '\f') {
        ++end;
    }

    if (*end != '\n' && *end != '\0') {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    if (*end == '\0' && buffer[sizeof buffer - 2] != '\n' && !feof(stdin)) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    if (!calculate_difference((uint64_t)value, &difference)) {
        fprintf(stderr, "Result is out of range\n");
        return 1;
    }

    printf("%" PRIu64 "\n", difference);
    return 0;
}