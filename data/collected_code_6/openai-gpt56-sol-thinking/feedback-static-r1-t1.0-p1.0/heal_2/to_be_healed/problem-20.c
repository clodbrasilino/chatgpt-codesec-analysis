#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

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

bool read_uint64(uint64_t *value)
{
    enum input_state {
        LEADING,
        SIGN,
        DIGITS,
        TRAILING
    };

    enum input_state state = LEADING;
    uint64_t result = 0;
    int ch;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != EOF) {
        unsigned char current = (unsigned char)ch;

        if (current == '\n') {
            if (state == DIGITS || state == TRAILING) {
                *value = result;
                return true;
            }
            return false;
        }

        if (state == LEADING) {
            if (isspace(current)) {
                continue;
            }

            if (current == '-') {
                return false;
            }

            if (current == '+') {
                state = SIGN;
                continue;
            }
        }

        if (state == LEADING || state == SIGN || state == DIGITS) {
            if (current >= '0' && current <= '9') {
                uint64_t digit = (uint64_t)(current - '0');

                if (result > (UINT64_MAX - digit) / 10) {
                    return false;
                }

                result = result * 10 + digit;
                state = DIGITS;
                continue;
            }

            if (state == DIGITS && isspace(current)) {
                state = TRAILING;
                continue;
            }

            return false;
        }

        if (!isspace(current)) {
            return false;
        }
    }

    if (ferror(stdin)) {
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