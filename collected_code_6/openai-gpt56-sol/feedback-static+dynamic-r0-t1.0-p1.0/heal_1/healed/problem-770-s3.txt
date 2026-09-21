#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <ctype.h>
#include <errno.h>

static int sum_fourth_powers_of_odds(uint64_t n, uint64_t *result)
{
    uint64_t sum = 0;

    if (result == NULL) {
        return -1;
    }

    for (uint64_t i = 0; i < n; ++i) {
        if (i > (UINT64_MAX - UINT64_C(1)) / UINT64_C(2)) {
            return -1;
        }

        uint64_t odd = UINT64_C(2) * i + UINT64_C(1);

        if (odd > UINT64_MAX / odd) {
            return -1;
        }

        uint64_t square = odd * odd;

        if (square > UINT64_MAX / square) {
            return -1;
        }

        uint64_t fourth_power = square * square;

        if (sum > UINT64_MAX - fourth_power) {
            return -1;
        }

        sum += fourth_power;
    }

    *result = sum;
    return 0;
}

static int read_uint64(uint64_t *value)
{
    char buffer[128];
    char *start;
    char *end;
    uintmax_t parsed;

    if (value == NULL || fgets(buffer, sizeof buffer, stdin) == NULL) {
        return -1;
    }

    start = buffer;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '-' || *start == '+') {
        return -1;
    }

    errno = 0;
    parsed = strtoumax(start, &end, 10);

    if (start == end || errno == ERANGE || parsed > UINT64_MAX) {
        return -1;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return -1;
    }

    *value = (uint64_t)parsed;
    return 0;
}

int main(void)
{
    uint64_t n;
    uint64_t sum;

    if (read_uint64(&n) != 0) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (sum_fourth_powers_of_odds(n, &sum) != 0) {
        fputs("Result exceeds the supported integer range\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}