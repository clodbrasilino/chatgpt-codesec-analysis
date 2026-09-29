#include <stdbool.h>
#include <stdio.h>

static bool is_digit(unsigned char ch)
{
    return ch >= (unsigned char)'0' && ch <= (unsigned char)'9';
}

static bool is_decimal_with_precision_2(const char *text)
{
    const unsigned char *p;
    size_t integer_digits = 0;

    if (text == NULL) {
        return false;
    }

    p = (const unsigned char *)text;

    if (*p == '\0') {
        return false;
    }

    if (*p == (unsigned char)'+' || *p == (unsigned char)'-') {
        ++p;
    }

    while (is_digit(*p)) {
        ++integer_digits;
        ++p;
    }

    if (integer_digits == 0 || *p != (unsigned char)'.') {
        return false;
    }

    ++p;

    if (!is_digit(*p)) {
        return false;
    }
    ++p;

    if (!is_digit(*p)) {
        return false;
    }
    ++p;

    return *p == '\0';
}

int main(void)
{
    char input[256];
    size_t length = 0;
    int ch;
    bool too_long = false;

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length + 1 < sizeof input) {
            input[length++] = (char)ch;
        } else {
            too_long = true;
        }
    }

    if (ch == EOF && ferror(stdin)) {
        return 1;
    }

    if (ch == EOF && length == 0 && !too_long) {
        return 0;
    }

    input[length] = '\0';

    if (too_long) {
        puts("Invalid");
        return 0;
    }

    puts(is_decimal_with_precision_2(input) ? "Valid" : "Invalid");
    return 0;
}