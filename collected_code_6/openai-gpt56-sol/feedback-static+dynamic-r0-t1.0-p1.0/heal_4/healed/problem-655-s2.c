#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int sum_of_fifth_powers(uint64_t n, uint64_t *result)
{
    const uint64_t maximum_n = 1388;
    __uint128_t sum = 0;

    if (result == NULL || n > maximum_n) {
        return -1;
    }

    for (uint64_t i = 1; i <= n; ++i) {
        const __uint128_t value = i;
        sum += value * value * value * value * value;
    }

    *result = (uint64_t)sum;
    return 0;
}

int main(void)
{
    char buffer[128];
    char *end;
    uintmax_t parsed;
    uint64_t result;

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    if (strchr(buffer, '\n') == NULL && !feof(stdin)) {
        int ch;

        while ((ch = getchar()) != '\n' && ch != EOF) {
        }

        fputs("Invalid input\n", stderr);
        return 1;
    }

    errno = 0;
    end = buffer;
    parsed = strtoumax(buffer, &end, 10);

    if (end == buffer || errno == ERANGE || parsed > UINT64_MAX ||
        buffer[0] == '-') {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\n' || *end == '\v' || *end == '\f') {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    if (sum_of_fifth_powers((uint64_t)parsed, &result) != 0) {
        fputs("Input is too large\n", stderr);
        return 1;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return 1;
    }

    return 0;
}