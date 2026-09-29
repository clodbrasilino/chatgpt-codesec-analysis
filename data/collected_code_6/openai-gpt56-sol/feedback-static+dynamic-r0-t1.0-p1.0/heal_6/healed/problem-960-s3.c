#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>
#include <stdint.h>

static int count_tilings(size_t n, uint64_t *result)
{
    uint64_t previous = 1;
    uint64_t current = 1;

    if (result == NULL) {
        return -1;
    }

    for (size_t i = 2; i <= n; ++i) {
        if (UINT64_MAX - current < previous) {
            return -1;
        }

        uint64_t next = current + previous;
        previous = current;
        current = next;
    }

    *result = current;
    return 0;
}

static int read_input(size_t *value)
{
    uintmax_t input = 0;
    int ch;
    int saw_digit = 0;
    int leading = 1;
    int trailing = 0;
    int overflow = 0;

    if (value == NULL) {
        return -1;
    }

    while ((ch = getchar()) != EOF) {
        unsigned char c = (unsigned char)ch;

        if (leading && isspace(c)) {
            continue;
        }

        leading = 0;

        if (isdigit(c)) {
            unsigned int digit;

            if (trailing) {
                return -1;
            }

            saw_digit = 1;
            digit = (unsigned int)(c - (unsigned char)'0');

            if (input > (UINTMAX_MAX - digit) / 10U) {
                overflow = 1;
            } else if (!overflow) {
                input = input * 10U + digit;
            }
        } else if (isspace(c)) {
            if (!saw_digit) {
                return -1;
            }
            trailing = 1;
        } else {
            return -1;
        }
    }

    if (ferror(stdin) || !saw_digit || overflow || input > SIZE_MAX) {
        return -1;
    }

    *value = (size_t)input;
    return 0;
}

int main(void)
{
    size_t input;
    uint64_t result;

    if (read_input(&input) != 0) {
        return EXIT_FAILURE;
    }

    if (count_tilings(input, &result) != 0) {
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}