#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool read_uint64_line(uint64_t *value)
{
    enum input_state {
        LEADING_SPACE,
        DIGITS,
        TRAILING_SPACE
    } state = LEADING_SPACE;

    uint64_t result = UINT64_C(0);
    bool have_digit = false;
    int input;

    if (value == NULL) {
        return false;
    }

    while ((input = fgetc(stdin)) != EOF) {
        unsigned char character = (unsigned char)input;

        if (character == '\n') {
            if (!have_digit) {
                return false;
            }

            *value = result;
            return true;
        }

        if (state == LEADING_SPACE) {
            if (isspace(character)) {
                continue;
            }

            if (character == '-') {
                return false;
            }

            if (character == '+') {
                state = DIGITS;
                continue;
            }

            state = DIGITS;
        }

        if (state == DIGITS) {
            if (character >= '0' && character <= '9') {
                uint64_t digit = (uint64_t)(character - '0');

                if (result > (UINT64_MAX - digit) / UINT64_C(10)) {
                    return false;
                }

                result = result * UINT64_C(10) + digit;
                have_digit = true;
                continue;
            }

            if (have_digit && isspace(character)) {
                state = TRAILING_SPACE;
                continue;
            }

            return false;
        }

        if (!isspace(character)) {
            return false;
        }
    }

    if (ferror(stdin) || !have_digit) {
        return false;
    }

    *value = result;
    return true;
}

static bool is_woodall(uint64_t number)
{
    for (uint64_t index = UINT64_C(1); index < UINT64_C(64); ++index) {
        if (index > (UINT64_MAX >> index)) {
            break;
        }

        uint64_t candidate = (index << index) - UINT64_C(1);

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

    if (!read_uint64_line(&value)) {
        return EXIT_FAILURE;
    }

    if (fputs(is_woodall(value)
                  ? "Woodall number\n"
                  : "Not a Woodall number\n",
              stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}