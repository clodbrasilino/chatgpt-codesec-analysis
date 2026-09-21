#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool read_uint64_line(uint64_t *value)
{
    enum {
        LEADING_SPACE,
        DIGITS,
        TRAILING_SPACE
    } state = LEADING_SPACE;

    uint64_t result = 0;
    bool have_digit = false;

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int character = fgetc(stdin);

        if (character == EOF) {
            if (ferror(stdin)) {
                return false;
            }
            break;
        }

        if (character == '\n') {
            break;
        }

        if (state == LEADING_SPACE) {
            if (isspace((unsigned char)character)) {
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

            if (isspace((unsigned char)character) && have_digit) {
                state = TRAILING_SPACE;
                continue;
            }

            return false;
        }

        if (!isspace((unsigned char)character)) {
            return false;
        }
    }

    if (!have_digit) {
        return false;
    }

    *value = result;
    return true;
}

static bool is_woodall(uint64_t number)
{
    for (uint64_t index = 1; index < 64; ++index) {
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

    const char *result = is_woodall(value)
        ? "Woodall number\n"
        : "Not a Woodall number\n";

    if (fputs(result, stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}