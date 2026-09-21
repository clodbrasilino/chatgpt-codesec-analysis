#include <ctype.h>
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

static int read_value(uint64_t *result)
{
    uintmax_t value;
    int ch;
    int digit_seen = 0;
    int overflow = 0;

    if (result == NULL) {
        return 0;
    }

    do {
        ch = getchar();
        if (ch == EOF) {
            return 0;
        }
    } while (isspace((unsigned char)ch) && ch != '\n');

    if (ch == '+') {
        ch = getchar();
    } else if (ch == '-') {
        while (ch != '\n' && ch != EOF) {
            ch = getchar();
        }
        return 0;
    }

    value = 0;

    while (ch != EOF && isdigit((unsigned char)ch)) {
        unsigned int digit = (unsigned int)(ch - '0');

        digit_seen = 1;

        if (value > (UINT64_MAX - digit) / 10U) {
            overflow = 1;
        } else if (!overflow) {
            value = value * 10U + digit;
        }

        ch = getchar();
    }

    while (ch != '\n' && ch != EOF) {
        if (!isspace((unsigned char)ch)) {
            do {
                ch = getchar();
            } while (ch != '\n' && ch != EOF);
            return 0;
        }
        ch = getchar();
    }

    if (!digit_seen || overflow) {
        return 0;
    }

    *result = (uint64_t)value;
    return 1;
}

int main(void)
{
    uint64_t value;
    uint64_t difference;

    if (!read_value(&value)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!calculate_difference(value, &difference)) {
        fputs("Result is out of range\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", difference);
    return EXIT_SUCCESS;
}