#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

static bool read_uint64(uint64_t *value)
{
    enum input_state {
        STATE_LEADING,
        STATE_AFTER_PLUS,
        STATE_DIGITS,
        STATE_TRAILING
    };

    unsigned char buffer[256];
    enum input_state state = STATE_LEADING;
    uint64_t result = UINT64_C(0);
    size_t count;

    if (value == NULL) {
        return false;
    }

    while ((count = fread(buffer, sizeof buffer[0], sizeof buffer, stdin)) > 0) {
        size_t index;

        for (index = 0; index < count; ++index) {
            unsigned char current = buffer[index];
            bool is_digit = current >= (unsigned char)'0' &&
                            current <= (unsigned char)'9';

            switch (state) {
            case STATE_LEADING:
                if (isspace(current)) {
                    continue;
                }
                if (current == (unsigned char)'+') {
                    state = STATE_AFTER_PLUS;
                    continue;
                }
                if (!is_digit) {
                    return false;
                }
                state = STATE_DIGITS;
                break;

            case STATE_AFTER_PLUS:
                if (!is_digit) {
                    return false;
                }
                state = STATE_DIGITS;
                break;

            case STATE_DIGITS:
                if (isspace(current)) {
                    state = STATE_TRAILING;
                    continue;
                }
                if (!is_digit) {
                    return false;
                }
                break;

            case STATE_TRAILING:
                if (!isspace(current)) {
                    return false;
                }
                continue;

            default:
                return false;
            }

            {
                uint64_t digit =
                    (uint64_t)(current - (unsigned char)'0');

                if (result > (UINT64_MAX - digit) / UINT64_C(10)) {
                    return false;
                }

                result = result * UINT64_C(10) + digit;
            }
        }
    }

    if (ferror(stdin)) {
        return false;
    }

    if (state != STATE_DIGITS && state != STATE_TRAILING) {
        return false;
    }

    *value = result;
    return true;
}

static bool is_woodall(uint64_t value)
{
    uint64_t n = UINT64_C(1);
    uint64_t power = UINT64_C(2);

    for (;;) {
        uint64_t product;
        uint64_t candidate;

        if (n > UINT64_MAX / power) {
            return false;
        }

        product = n * power;
        candidate = product - UINT64_C(1);

        if (candidate == value) {
            return true;
        }

        if (candidate > value || power > UINT64_MAX / UINT64_C(2)) {
            return false;
        }

        ++n;
        power *= UINT64_C(2);
    }
}

int main(void)
{
    uint64_t value;

    if (!read_uint64(&value)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    puts(is_woodall(value) ? "Woodall number" : "Not a Woodall number");
    return EXIT_SUCCESS;
}