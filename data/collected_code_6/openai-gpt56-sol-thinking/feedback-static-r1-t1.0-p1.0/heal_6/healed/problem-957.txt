#include <ctype.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint32_t get_rightmost_set_bit_position(uint32_t value)
{
    uint32_t position = 0U;

    while (value != 0U) {
        ++position;

        if ((value & UINT32_C(1)) != 0U) {
            return position;
        }

        value >>= 1U;
    }

    return 0U;
}

static bool read_uint32_line(uint32_t *value)
{
    enum parser_state {
        STATE_LEADING,
        STATE_EXPECT_DIGIT,
        STATE_DIGITS,
        STATE_TRAILING,
        STATE_INVALID
    };

    enum parser_state state = STATE_LEADING;
    uint32_t result = 0U;
    int character;

    if (value == NULL) {
        return false;
    }

    while ((character = fgetc(stdin)) != EOF) {
        uint32_t digit;

        if (character == '\n') {
            break;
        }

        switch (state) {
        case STATE_LEADING:
            if (isspace((unsigned char)character) != 0) {
                continue;
            }

            if (character == '+') {
                state = STATE_EXPECT_DIGIT;
                continue;
            }

            if (character < '0' || character > '9') {
                state = STATE_INVALID;
                continue;
            }

            state = STATE_DIGITS;
            break;

        case STATE_EXPECT_DIGIT:
            if (character < '0' || character > '9') {
                state = STATE_INVALID;
                continue;
            }

            state = STATE_DIGITS;
            break;

        case STATE_DIGITS:
            if (character >= '0' && character <= '9') {
                break;
            }

            if (isspace((unsigned char)character) != 0) {
                state = STATE_TRAILING;
            } else {
                state = STATE_INVALID;
            }

            continue;

        case STATE_TRAILING:
            if (isspace((unsigned char)character) == 0) {
                state = STATE_INVALID;
            }

            continue;

        case STATE_INVALID:
            continue;
        }

        digit = (uint32_t)(character - '0');

        if (result > (UINT32_MAX - digit) / UINT32_C(10)) {
            state = STATE_INVALID;
            continue;
        }

        result = result * UINT32_C(10) + digit;
    }

    if (ferror(stdin) != 0) {
        return false;
    }

    if (state != STATE_DIGITS && state != STATE_TRAILING) {
        return false;
    }

    *value = result;
    return true;
}

int main(void)
{
    uint32_t value;

    if (!read_uint32_line(&value)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu32 "\n", get_rightmost_set_bit_position(value));

    return EXIT_SUCCESS;
}