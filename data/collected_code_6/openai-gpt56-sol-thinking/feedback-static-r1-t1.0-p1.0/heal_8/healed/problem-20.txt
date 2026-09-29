#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_INPUT_CHARACTERS 4096U

static bool append_digit(uint64_t *result, unsigned char c)
{
    uint64_t digit = (uint64_t)(c - (unsigned char)'0');

    if (*result > UINT64_MAX / 10 ||
        (*result == UINT64_MAX / 10 && digit > UINT64_MAX % 10)) {
        return false;
    }

    *result = *result * 10 + digit;
    return true;
}

bool read_uint64(uint64_t *value)
{
    enum parse_state {
        PARSE_LEADING,
        PARSE_SIGN,
        PARSE_DIGITS,
        PARSE_TRAILING,
        PARSE_INVALID
    };

    enum parse_state state = PARSE_LEADING;
    uint64_t result = 0;
    size_t input_length = 0;
    int ch;

    if (value == NULL) {
        return false;
    }

    while ((ch = fgetc(stdin)) != EOF) {
        unsigned char c;

        if (ch == '\n') {
            break;
        }

        if (input_length >= MAX_INPUT_CHARACTERS) {
            return false;
        }
        ++input_length;

        c = (unsigned char)ch;

        switch (state) {
        case PARSE_LEADING:
            if (isspace(c)) {
                break;
            }

            if (c == (unsigned char)'+') {
                state = PARSE_SIGN;
                break;
            }

            if (c >= (unsigned char)'0' && c <= (unsigned char)'9') {
                state = PARSE_DIGITS;
                if (!append_digit(&result, c)) {
                    state = PARSE_INVALID;
                }
            } else {
                state = PARSE_INVALID;
            }
            break;

        case PARSE_SIGN:
            if (c >= (unsigned char)'0' && c <= (unsigned char)'9') {
                state = PARSE_DIGITS;
                if (!append_digit(&result, c)) {
                    state = PARSE_INVALID;
                }
            } else {
                state = PARSE_INVALID;
            }
            break;

        case PARSE_DIGITS:
            if (c >= (unsigned char)'0' && c <= (unsigned char)'9') {
                if (!append_digit(&result, c)) {
                    state = PARSE_INVALID;
                }
            } else if (isspace(c)) {
                state = PARSE_TRAILING;
            } else {
                state = PARSE_INVALID;
            }
            break;

        case PARSE_TRAILING:
            if (!isspace(c)) {
                state = PARSE_INVALID;
            }
            break;

        case PARSE_INVALID:
            break;
        }
    }

    if (ferror(stdin)) {
        return false;
    }

    if (state != PARSE_DIGITS && state != PARSE_TRAILING) {
        return false;
    }

    *value = result;
    return true;
}

bool is_woodall(uint64_t value)
{
    uint64_t n = 1;
    uint64_t power = 2;

    for (;;) {
        uint64_t candidate;

        if (n > UINT64_MAX / power) {
            return false;
        }

        candidate = n * power - 1;

        if (candidate == value) {
            return true;
        }

        if (candidate > value || power > UINT64_MAX / 2) {
            return false;
        }

        ++n;
        power *= 2;
    }
}

int main(void)
{
    uint64_t value;

    if (!read_uint64(&value)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (is_woodall(value)) {
        puts("Woodall number");
    } else {
        puts("Not a Woodall number");
    }

    return EXIT_SUCCESS;
}