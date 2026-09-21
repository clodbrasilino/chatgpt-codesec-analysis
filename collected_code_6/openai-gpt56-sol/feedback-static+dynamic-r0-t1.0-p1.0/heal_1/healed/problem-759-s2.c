#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

static bool is_decimal_with_precision_2(const char *text)
{
    const unsigned char *p = (const unsigned char *)text;
    size_t integer_digits = 0;

    if (p == NULL || *p == '\0') {
        return false;
    }

    if (*p == '+' || *p == '-') {
        ++p;
    }

    while (*p >= '0' && *p <= '9') {
        ++integer_digits;
        ++p;
    }

    if (integer_digits == 0 || *p != '.') {
        return false;
    }

    ++p;

    if (*p < '0' || *p > '9') {
        return false;
    }

    ++p;

    if (*p < '0' || *p > '9') {
        return false;
    }

    ++p;

    return *p == '\0';
}

int main(void)
{
    enum { INPUT_CAPACITY = 256 };
    char input[INPUT_CAPACITY];
    size_t length = 0;
    int character;
    bool too_long = false;

    while ((character = fgetc(stdin)) != '\n' && character != EOF) {
        if (length + 1 < sizeof input) {
            input[length++] = (char)character;
        } else {
            too_long = true;
        }
    }

    if (ferror(stdin)) {
        fputs("Input error\n", stderr);
        return 1;
    }

    if (character == EOF && length == 0 && !too_long) {
        fputs("Input error\n", stderr);
        return 1;
    }

    if (too_long) {
        fputs("Input too long\n", stderr);
        return 1;
    }

    input[length] = '\0';

    puts(is_decimal_with_precision_2(input) ? "Valid" : "Invalid");
    return 0;
}