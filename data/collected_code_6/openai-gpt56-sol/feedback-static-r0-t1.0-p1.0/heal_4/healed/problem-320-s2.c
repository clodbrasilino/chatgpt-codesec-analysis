#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int calculate_difference(uint64_t n, uint64_t *result)
{
    __uint128_t value;
    __uint128_t sum;
    __uint128_t sum_of_squares;
    __uint128_t difference;

    if (result == NULL) {
        return 0;
    }

    value = n;
    sum = value * (value + 1) / 2;
    sum_of_squares = value * (value + 1) * (2 * value + 1) / 6;
    difference = sum * sum - sum_of_squares;

    if (difference > UINT64_MAX) {
        return 0;
    }

    *result = (uint64_t)difference;
    return 1;
}

static int read_uint64(uint64_t *value)
{
    uintmax_t parsed;
    int ch;
    int first;
    int digit_seen;
    int trailing_space;

    if (value == NULL) {
        return 0;
    }

    parsed = 0;
    first = 1;
    digit_seen = 0;
    trailing_space = 0;

    while ((ch = getchar()) != '\n' && ch != EOF) {
        unsigned char c = (unsigned char)ch;

        if (first) {
            while (isspace(c) && c != '\n') {
                ch = getchar();
                if (ch == '\n' || ch == EOF) {
                    break;
                }
                c = (unsigned char)ch;
            }

            if (ch == '\n' || ch == EOF) {
                break;
            }

            if (c == '+') {
                first = 0;
                continue;
            }

            if (c == '-') {
                return 0;
            }

            first = 0;
        }

        if (isdigit(c)) {
            unsigned int digit = (unsigned int)(c - (unsigned char)'0');

            if (trailing_space) {
                return 0;
            }

            if (parsed > (UINT64_MAX - digit) / 10) {
                return 0;
            }

            parsed = parsed * 10 + digit;
            digit_seen = 1;
        } else if (isspace(c)) {
            if (digit_seen) {
                trailing_space = 1;
            }
        } else {
            return 0;
        }
    }

    if (ferror(stdin) || !digit_seen) {
        return 0;
    }

    if (ch == '\n') {
        int extra = getchar();

        if (extra != EOF) {
            return 0;
        }

        if (ferror(stdin)) {
            return 0;
        }
    }

    *value = (uint64_t)parsed;
    return 1;
}

int main(void)
{
    uint64_t input;
    uint64_t difference;

    errno = 0;

    if (!read_uint64(&input)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!calculate_difference(input, &difference)) {
        fputs("Result exceeds the supported range\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", difference) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}