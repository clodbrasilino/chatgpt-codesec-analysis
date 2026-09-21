#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

enum input_state {
    INPUT_LEADING_SPACE,
    INPUT_AFTER_PLUS,
    INPUT_DIGITS,
    INPUT_TRAILING_SPACE
};

static bool is_decimal_digit(unsigned char ch)
{
    return ch >= (unsigned char)'0' && ch <= (unsigned char)'9';
}

static bool append_digit(uint64_t *value, unsigned char ch)
{
    uint64_t digit = (uint64_t)(ch - (unsigned char)'0');

    if (*value > (UINT64_MAX - digit) / UINT64_C(10)) {
        return false;
    }

    *value = (*value * UINT64_C(10)) + digit;
    return true;
}

static bool process_input_character(
    enum input_state *state,
    uint64_t *value,
    unsigned char ch)
{
    switch (*state) {
    case INPUT_LEADING_SPACE:
        if (isspace((int)ch) != 0) {
            return true;
        }

        if (ch == (unsigned char)'+') {
            *state = INPUT_AFTER_PLUS;
            return true;
        }

        if (!is_decimal_digit(ch) || !append_digit(value, ch)) {
            return false;
        }

        *state = INPUT_DIGITS;
        return true;

    case INPUT_AFTER_PLUS:
        if (!is_decimal_digit(ch) || !append_digit(value, ch)) {
            return false;
        }

        *state = INPUT_DIGITS;
        return true;

    case INPUT_DIGITS:
        if (is_decimal_digit(ch)) {
            return append_digit(value, ch);
        }

        if (isspace((int)ch) != 0) {
            *state = INPUT_TRAILING_SPACE;
            return true;
        }

        return false;

    case INPUT_TRAILING_SPACE:
        return isspace((int)ch) != 0;
    }

    return false;
}

static bool read_uint64(uint64_t *value)
{
    unsigned char buffer[4096];
    enum input_state state = INPUT_LEADING_SPACE;
    uint64_t result = UINT64_C(0);

    if (value == NULL) {
        return false;
    }

    for (;;) {
        size_t bytes_read = fread(buffer, sizeof buffer[0], sizeof buffer, stdin);

        for (size_t i = 0; i < bytes_read; ++i) {
            if (!process_input_character(&state, &result, buffer[i])) {
                return false;
            }
        }

        if (bytes_read < sizeof buffer) {
            if (ferror(stdin) != 0) {
                return false;
            }

            break;
        }
    }

    if (state != INPUT_DIGITS && state != INPUT_TRAILING_SPACE) {
        return false;
    }

    *value = result;
    return true;
}

static bool is_woodall(uint64_t number)
{
    for (uint64_t index = UINT64_C(1); index < UINT64_C(64); ++index) {
        uint64_t candidate;

        if (index > (UINT64_MAX >> index)) {
            break;
        }

        candidate = (index << index) - UINT64_C(1);

        if (candidate == number) {
            return true;
        }

        if (candidate > number) {
            break;
        }
    }

    return false;
}

int main(void)
{
    uint64_t value;
    const char *result;

    if (!read_uint64(&value)) {
        return EXIT_FAILURE;
    }

    result = is_woodall(value)
        ? "Woodall number\n"
        : "Not a Woodall number\n";

    if (fputs(result, stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}