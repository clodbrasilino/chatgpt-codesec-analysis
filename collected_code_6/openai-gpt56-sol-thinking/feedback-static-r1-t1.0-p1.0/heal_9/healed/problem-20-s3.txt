#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_INPUT_LENGTH 256U

static bool read_uint64_line(uint64_t *value)
{
    uint64_t result = UINT64_C(0);
    size_t input_length = 0U;
    bool saw_sign = false;
    bool saw_digit = false;
    bool trailing_space = false;
    int input;

    if (value == NULL) {
        return false;
    }

    while ((input = fgetc(stdin)) != EOF) {
        unsigned char c = (unsigned char)input;

        if (c == (unsigned char)'\n') {
            break;
        }

        if (input_length >= MAX_INPUT_LENGTH) {
            return false;
        }
        ++input_length;

        if (c == (unsigned char)'\0') {
            return false;
        }

        if (!saw_digit) {
            if (isspace((int)c) != 0) {
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

            if (isdigit((int)c) == 0) {
                return false;
            }
        } else {
            if (isspace((int)c) != 0) {
                trailing_space = true;
                continue;
            }

            if (trailing_space || isdigit((int)c) == 0) {
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

    if (input == EOF && ferror(stdin) != 0) {
        return false;
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
    const char *message;

    if (!read_uint64_line(&value)) {
        return EXIT_FAILURE;
    }

    message = is_woodall(value)
                  ? "Woodall number\n"
                  : "Not a Woodall number\n";

    if (fputs(message, stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}