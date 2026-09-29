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

    enum input_state state = STATE_LEADING;
    uint64_t result = UINT64_C(0);
    int ch;

    if (value == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != EOF) {
        bool is_digit = ch >= '0' && ch <= '9';

        switch (state) {
        case STATE_LEADING:
            if (isspace((unsigned char)ch)) {
                continue;
            }
            if (ch == '+') {
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
            if (isspace((unsigned char)ch)) {
                state = STATE_TRAILING;
                continue;
            }
            if (!is_digit) {
                return false;
            }
            break;

        case STATE_TRAILING:
            if (!isspace((unsigned char)ch)) {
                return false;
            }
            continue;

        default:
            return false;
        }

        {
            uint64_t digit = (uint64_t)(ch - '0');

            if (result > (UINT64_MAX - digit) / UINT64_C(10)) {
                return false;
            }

            result = result * UINT64_C(10) + digit;
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

        if (candidate > value) {
            return false;
        }

        if (power > UINT64_MAX / UINT64_C(2)) {
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