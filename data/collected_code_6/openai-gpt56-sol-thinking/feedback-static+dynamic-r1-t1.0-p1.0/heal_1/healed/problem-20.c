#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

static bool read_uint64(uint64_t *value)
{
    uint64_t result = 0;
    int ch;

    do {
        ch = fgetc(stdin);
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == '+') {
        ch = fgetc(stdin);
    }

    if (ch == EOF || !isdigit((unsigned char)ch)) {
        return false;
    }

    do {
        uint64_t digit = (uint64_t)(ch - '0');

        if (result > (UINT64_MAX - digit) / 10) {
            return false;
        }

        result = result * 10 + digit;
        ch = fgetc(stdin);
    } while (ch != EOF && isdigit((unsigned char)ch));

    while (ch != EOF) {
        if (!isspace((unsigned char)ch)) {
            return false;
        }

        ch = fgetc(stdin);
    }

    if (ferror(stdin)) {
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