#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool read_uint64_line(uint64_t *value)
{
    uint64_t result = UINT64_C(0);
    bool saw_sign = false;
    bool saw_digit = false;
    bool trailing_space = false;

    if (value == NULL) {
        return false;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char input[2];
        unsigned char c;

        if (fgets(input, sizeof input, stdin) == NULL) {
            if (ferror(stdin)) {
                return false;
            }
            break;
        }

        c = (unsigned char)input[0];

        if (c == '\0') {
            return false;
        }

        if (c == '\n') {
            break;
        }

        if (!saw_digit) {
            if (isspace(c)) {
                if (saw_sign) {
                    return false;
                }
                continue;
            }

            if (c == (unsigned char)'+') {
                if (saw_sign) {
                    return false;
                }
                saw_sign = true;
                continue;
            }

            if (c < (unsigned char)'0' || c > (unsigned char)'9') {
                return false;
            }
        } else {
            if (isspace(c)) {
                trailing_space = true;
                continue;
            }

            if (trailing_space ||
                c < (unsigned char)'0' ||
                c > (unsigned char)'9') {
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

    if (!saw_digit) {
        return false;
    }

    *value = result;
    return true;
}

static bool is_woodall(uint64_t number)
{
    for (uint64_t index = UINT64_C(1);
         index < UINT64_C(64);
         ++index) {
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