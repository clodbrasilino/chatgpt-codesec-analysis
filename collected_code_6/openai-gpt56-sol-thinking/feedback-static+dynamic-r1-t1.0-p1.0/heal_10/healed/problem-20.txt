#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define INPUT_MAX_LENGTH 256U

static bool read_uint64(uint64_t *value)
{
    unsigned char input[INPUT_MAX_LENGTH];
    size_t length;
    size_t index = 0;
    uint64_t result = UINT64_C(0);
    bool has_digit = false;

    if (value == NULL) {
        return false;
    }

    length = fread(input, 1, sizeof input, stdin);

    if (ferror(stdin) || length == sizeof input) {
        return false;
    }

    while (index < length && isspace(input[index])) {
        ++index;
    }

    if (index < length && input[index] == '+') {
        ++index;
    }

    while (index < length && input[index] >= '0' && input[index] <= '9') {
        uint64_t digit = (uint64_t)(input[index] - '0');

        if (result > (UINT64_MAX - digit) / UINT64_C(10)) {
            return false;
        }

        result = result * UINT64_C(10) + digit;
        has_digit = true;
        ++index;
    }

    if (!has_digit) {
        return false;
    }

    while (index < length && isspace(input[index])) {
        ++index;
    }

    if (index != length) {
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