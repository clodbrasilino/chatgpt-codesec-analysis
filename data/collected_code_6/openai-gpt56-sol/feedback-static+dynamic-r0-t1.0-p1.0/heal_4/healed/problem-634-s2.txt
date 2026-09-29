#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_fourth_powers_even(uint64_t n, uint64_t *result)
{
    uint64_t sum = 0;

    if (result == NULL) {
        return 0;
    }

    for (uint64_t i = 1; i <= n; ++i) {
        uint64_t even;
        uint64_t square;
        uint64_t fourth_power;

        if (i > UINT64_MAX / UINT64_C(2)) {
            return 0;
        }
        even = i * UINT64_C(2);

        if (even != 0 && even > UINT64_MAX / even) {
            return 0;
        }
        square = even * even;

        if (square != 0 && square > UINT64_MAX / square) {
            return 0;
        }
        fourth_power = square * square;

        if (sum > UINT64_MAX - fourth_power) {
            return 0;
        }
        sum += fourth_power;
    }

    *result = sum;
    return 1;
}

static int read_uint64(uint64_t *value)
{
    uintmax_t parsed;
    char *line = NULL;
    char *end = NULL;
    size_t capacity = 0;
    ssize_t length;

    if (value == NULL) {
        return 0;
    }

    length = getline(&line, &capacity, stdin);
    if (length < 0) {
        free(line);
        return 0;
    }

    errno = 0;
    parsed = strtoumax(line, &end, 10);

    if (end == line || errno == ERANGE || parsed > UINT64_MAX) {
        free(line);
        return 0;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(line);
        return 0;
    }

    *value = (uint64_t)parsed;
    free(line);
    return 1;
}

int main(void)
{
    uint64_t value;
    uint64_t result;

    if (!read_uint64(&value)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!sum_fourth_powers_even(value, &result)) {
        fputs("Result exceeds the supported range\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}