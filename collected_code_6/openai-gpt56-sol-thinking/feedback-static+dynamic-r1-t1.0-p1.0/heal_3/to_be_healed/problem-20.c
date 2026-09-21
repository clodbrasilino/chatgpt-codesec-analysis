#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

static bool read_uint64(uint64_t *value)
{
    enum {
        STATE_LEADING,
        STATE_AFTER_PLUS,
        STATE_DIGITS,
        STATE_TRAILING
    } state = STATE_LEADING;

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char buffer[4096];
    uint64_t result = 0;
    size_t count;

    if (value == NULL) {
        return false;
    }

    while ((count = fread(buffer, 1, sizeof buffer, stdin)) != 0) {
        for (size_t i = 0; i < count; ++i) {
            unsigned char ch = buffer[i];

            switch (state) {
            case STATE_LEADING:
                if (isspace(ch)) {
                    continue;
                }
                if (ch == '+') {
                    state = STATE_AFTER_PLUS;
                    continue;
                }
                if (!isdigit(ch)) {
                    return false;
                }
                state = STATE_DIGITS;
                break;

            case STATE_AFTER_PLUS:
                if (!isdigit(ch)) {
                    return false;
                }
                state = STATE_DIGITS;
                break;

            case STATE_DIGITS:
                if (isspace(ch)) {
                    state = STATE_TRAILING;
                    continue;
                }
                if (!isdigit(ch)) {
                    return false;
                }
                break;

            case STATE_TRAILING:
                if (!isspace(ch)) {
                    return false;
                }
                continue;

            default:
                return false;
            }

            {
                uint64_t digit = (uint64_t)(ch - (unsigned char)'0');

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
    uint64_t n = 1;
    uint64_t power = 2;

    for (;;) {
        uint64_t candidate;

        if (n > UINT64_MAX / power) {
            return false;
        }

        candidate = n * power - UINT64_C(1);

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

    if (is_woodall(value)) {
        puts("Woodall number");
    } else {
        puts("Not a Woodall number");
    }

    return EXIT_SUCCESS;
}