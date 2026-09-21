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

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char buffer[4096];
    uint64_t result = 0;
    bool have_digit = false;

    if (value == NULL) {
        return false;
    }

    for (;;) {
        size_t count = fread(buffer, sizeof buffer[0],
                             sizeof buffer / sizeof buffer[0], stdin);

        for (size_t i = 0; i < count; ++i) {
            unsigned char character = buffer[i];

            if (character == '\n') {
                if (!have_digit) {
                    return false;
                }

                *value = result;
                return true;
            }

            if (state == LEADING_SPACE) {
                if (isspace(character)) {
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

                if (isspace(character) && have_digit) {
                    state = TRAILING_SPACE;
                    continue;
                }

                return false;
            }

            if (!isspace(character)) {
                return false;
            }
        }

        if (ferror(stdin)) {
            return false;
        }

        if (feof(stdin)) {
            break;
        }

        if (count == 0) {
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