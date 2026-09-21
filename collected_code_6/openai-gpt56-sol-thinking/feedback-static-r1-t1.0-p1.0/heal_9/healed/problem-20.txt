#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_INPUT_CHARACTERS 4096U

static bool append_digit(uint64_t *result, unsigned char character)
{
    uint64_t digit = (uint64_t)(character - (unsigned char)'0');

    if (*result > UINT64_MAX / 10U ||
        (*result == UINT64_MAX / 10U && digit > UINT64_MAX % 10U)) {
        return false;
    }

    *result = (*result * 10U) + digit;
    return true;
}

static bool read_uint64(uint64_t *value)
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

    if (value == NULL) {
        return false;
    }

    for (;;) {
        unsigned char character;

        if (fread(&character, sizeof character, 1U, stdin) != 1U) {
            if (ferror(stdin)) {
                return false;
            }
            break;
        }

        if (character == (unsigned char)'\n') {
            break;
        }

        if (input_length == MAX_INPUT_CHARACTERS) {
            return false;
        }

        ++input_length;

        switch (state) {
        case PARSE_LEADING:
            if (isspace(character)) {
                break;
            }

            if (character == (unsigned char)'+') {
                state = PARSE_SIGN;
            } else if (isdigit(character)) {
                state = PARSE_DIGITS;
                if (!append_digit(&result, character)) {
                    state = PARSE_INVALID;
                }
            } else {
                state = PARSE_INVALID;
            }
            break;

        case PARSE_SIGN:
            if (isdigit(character)) {
                state = PARSE_DIGITS;
                if (!append_digit(&result, character)) {
                    state = PARSE_INVALID;
                }
            } else {
                state = PARSE_INVALID;
            }
            break;

        case PARSE_DIGITS:
            if (isdigit(character)) {
                if (!append_digit(&result, character)) {
                    state = PARSE_INVALID;
                }
            } else if (isspace(character)) {
                state = PARSE_TRAILING;
            } else {
                state = PARSE_INVALID;
            }
            break;

        case PARSE_TRAILING:
            if (!isspace(character)) {
                state = PARSE_INVALID;
            }
            break;

        case PARSE_INVALID:
            break;
        }
    }

    if (state != PARSE_DIGITS && state != PARSE_TRAILING) {
        return false;
    }

    *value = result;
    return true;
}

static bool is_woodall(uint64_t value)
{
    uint64_t n = 1U;
    uint64_t power = 2U;

    for (;;) {
        uint64_t product;
        uint64_t candidate;

        if (n > UINT64_MAX / power) {
            return false;
        }

        product = n * power;
        candidate = product - 1U;

        if (candidate == value) {
            return true;
        }

        if (candidate > value || power > UINT64_MAX / 2U) {
            return false;
        }

        ++n;
        power *= 2U;
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