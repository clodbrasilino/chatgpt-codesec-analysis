#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool read_uint64_line(uint64_t *value)
{
    uint64_t result = UINT64_C(0);
    bool saw_input = false;
    bool saw_sign = false;
    bool saw_digit = false;
    bool trailing_space = false;
    int ch;

    if (value == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != EOF) {
        unsigned char c;

        saw_input = true;

        if (ch == '\n') {
            break;
        }

        c = (unsigned char)ch;

        if (c == '\0') {
            return false;
        }

        if (!saw_digit) {
            if (isspace(c)) {
                if (saw_sign) {
                    return false;
                }
                continue;
            }

            if (c == '+') {
                if (saw_sign) {
                    return false;
                }
                saw_sign = true;
                continue;
            }

            if (c < '0' || c > '9') {
                return false;
            }
        } else {
            if (isspace(c)) {
                trailing_space = true;
                continue;
            }

            if (trailing_space || c < '0' || c > '9') {
                return false;
            }
        }

        {
            uint64_t digit = (uint64_t)(c - (unsigned char)'0');

            if (result > (UINT64_MAX - digit) / UINT64_C(10)) {
                return false;
            }

            result = result * UINT64_C(10) + digit;
            saw_digit = true;
        }
    }

    if (ferror(stdin) || (!saw_input && ch == EOF) || !saw_digit) {
        return false;
    }

    *value = result;
    return true;
}

static bool is_woodall(uint64_t number)
{
    for (uint64_t index = UINT64_C(1); index < UINT64_C(64); ++index) {
        uint64_t candidate;

        if (index > (UINT64_MAX >> index)) {
            break;
        }

        candidate = (index << index) - UINT64_C(1);

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