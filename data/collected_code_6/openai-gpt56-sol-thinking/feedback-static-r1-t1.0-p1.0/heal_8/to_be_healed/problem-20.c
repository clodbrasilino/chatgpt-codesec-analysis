#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

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
    bool received_input = false;
    int ch;

    if (value == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != EOF) {
        unsigned char c;

        received_input = true;

        if (ch == '\n') {
            break;
        }

        c = (unsigned char)ch;

        switch (state) {
        case PARSE_LEADING:
            if (isspace(c)) {
                break;
            }

            if (c == '+') {
                state = PARSE_SIGN;
                break;
            }

            if (c >= '0' && c <= '9') {
                state = PARSE_DIGITS;
            } else {
                state = PARSE_INVALID;
                break;
            }

            goto process_digit;

        case PARSE_SIGN:
            if (c < '0' || c > '9') {
                state = PARSE_INVALID;
                break;
            }

            state = PARSE_DIGITS;
            goto process_digit;

        case PARSE_DIGITS:
            if (c >= '0' && c <= '9') {
                uint64_t digit;

process_digit:
                digit = (uint64_t)(c - '0');

                if (result > UINT64_MAX / 10 ||
                    (result == UINT64_MAX / 10 &&
                     digit > UINT64_MAX % 10)) {
                    state = PARSE_INVALID;
                    break;
                }

                result = result * 10 + digit;
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

    if (ferror(stdin) || !received_input || state != PARSE_DIGITS) {
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