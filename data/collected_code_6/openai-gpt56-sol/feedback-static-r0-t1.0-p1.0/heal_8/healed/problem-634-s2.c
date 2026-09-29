#include <ctype.h>
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

        even = UINT64_C(2) * i;

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
    char buffer[128];
    char *p;
    char *end;
    uintmax_t parsed;

    if (value == NULL) {
        return 0;
    }

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return 0;
    }

    if (strchr(buffer, '\n') == NULL && !feof(stdin)) {
        int ch;

        do {
            ch = getchar();
        } while (ch != '\n' && ch != EOF);

        return 0;
    }

    p = buffer;

    while (isspace((unsigned char)*p)) {
        ++p;
    }

    if (*p == '\0' || *p == '+' || *p == '-') {
        return 0;
    }

    if (!isdigit((unsigned char)*p)) {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(p, &end, 10);

    if (p == end || errno == ERANGE || parsed > UINT64_MAX) {
        return 0;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return 0;
    }

    *value = (uint64_t)parsed;
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

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}