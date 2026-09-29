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
    enum parse_state {
        PARSE_LEADING,
        PARSE_SIGN,
        PARSE_DIGITS,
        PARSE_TRAILING
    };

    enum parse_state state = PARSE_LEADING;
    uint32_t result = 0U;
    bool valid = true;
    bool end_of_line = false;

    if (value == NULL) {
        return false;
    }

    while (!end_of_line) {
        unsigned char byte;
        int character;

        if (fread(&byte, sizeof byte, 1U, stdin) != 1U) {
            if (ferror(stdin) != 0) {
                return false;
            }

            break;
        }

        character = (int)byte;

        if (character == '\n') {
            break;
        }

        if (!valid) {
            continue;
        }

        switch (state) {
        case PARSE_LEADING:
            if (isspace((unsigned char)character) != 0) {
                continue;
            }

            if (character == '+') {
                state = PARSE_SIGN;
                continue;
            }

            if (character >= '0' && character <= '9') {
                state = PARSE_DIGITS;
            } else {
                valid = false;
                continue;
            }
            break;

        case PARSE_SIGN:
            if (character >= '0' && character <= '9') {
                state = PARSE_DIGITS;
            } else {
                valid = false;
                continue;
            }
            break;

        case PARSE_DIGITS:
            if (character >= '0' && character <= '9') {
                break;
            }

            if (isspace((unsigned char)character) != 0) {
                state = PARSE_TRAILING;
                continue;
            }

            valid = false;
            continue;

        case PARSE_TRAILING:
            if (isspace((unsigned char)character) == 0) {
                valid = false;
            }
            continue;
        }

        {
            uint32_t digit = (uint32_t)(character - '0');

            if (result > (UINT32_MAX - digit) / UINT32_C(10)) {
                valid = false;
                continue;
            }

            result = result * UINT32_C(10) + digit;
        }
    }

    if (!valid || (state != PARSE_DIGITS && state != PARSE_TRAILING)) {
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