#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_woodall(uint64_t number)
{
    uint64_t power = 2;

    if (number == 0) {
        return false;
    }

    for (uint64_t index = 1; ; ++index) {
        if (index > UINT64_MAX / power) {
            return false;
        }

        uint64_t candidate = index * power - 1;

        if (candidate == number) {
            return true;
        }

        if (candidate > number || power > UINT64_MAX / 2) {
            return false;
        }

        power *= 2;
    }
}

static bool read_uint64_line(FILE *stream, uint64_t *value)
{
    enum parser_state {
        LEADING,
        SIGN,
        DIGITS,
        TRAILING
    };

    enum parser_state state = LEADING;
    uint64_t result = 0;
    unsigned char current;

    while (fread(&current, sizeof current, 1, stream) == 1) {
        if (current == '\n') {
            break;
        }

        switch (state) {
        case LEADING:
            if (isspace(current)) {
                continue;
            }

            if (current == '+') {
                state = SIGN;
                continue;
            }

            if (current < '0' || current > '9') {
                return false;
            }

            state = DIGITS;
            break;

        case SIGN:
            if (current < '0' || current > '9') {
                return false;
            }

            state = DIGITS;
            break;

        case DIGITS:
            if (current >= '0' && current <= '9') {
                break;
            }

            if (isspace(current)) {
                state = TRAILING;
                continue;
            }

            return false;

        case TRAILING:
            if (!isspace(current)) {
                return false;
            }

            continue;
        }

        uint64_t digit = (uint64_t)(current - '0');

        if (result > (UINT64_MAX - digit) / 10) {
            return false;
        }

        result = result * 10 + digit;
    }

    if (ferror(stream)) {
        return false;
    }

    if (state != DIGITS && state != TRAILING) {
        return false;
    }

    *value = result;
    return true;
}

int main(void)
{
    uint64_t number;

    if (!read_uint64_line(stdin, &number)) {
        return EXIT_FAILURE;
    }

    printf("%s\n",
           is_woodall(number) ? "Woodall number" : "Not a Woodall number");

    return EXIT_SUCCESS;
}