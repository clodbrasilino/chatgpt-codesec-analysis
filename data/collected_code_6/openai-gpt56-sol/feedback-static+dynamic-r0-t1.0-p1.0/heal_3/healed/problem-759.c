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

    if (text == NULL || *text == '\0') {
        return false;
    }

    p = (const unsigned char *)text;

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

    if (!is_digit(p[0])) {
        return false;
    }

    ++p;

    if (!is_digit(p[0])) {
        return false;
    }

    ++p;

    return *p == '\0';
}

int main(void)
{
    char input[256];
    size_t length;
    int ch;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return ferror(stdin) ? 1 : 0;
    }

    for (length = 0; length < sizeof input && input[length] != '\0'; ++length) {
        if (input[length] == '\n') {
            input[length] = '\0';
            break;
        }
    }

    if (length == sizeof input) {
        return 1;
    }

    if (input[length] != '\0') {
        return 1;
    }

    if (length == sizeof input - 1 && input[length] == '\0') {
        ch = fgetc(stdin);

        if (ch != '\n' && ch != EOF) {
            while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
            }

            if (ferror(stdin)) {
                return 1;
            }

            puts("Invalid");
            return 0;
        }

        if (ch == EOF && ferror(stdin)) {
            return 1;
        }
    }

    if (length > 0 && input[length - 1] == '\r') {
        input[length - 1] = '\0';
    }

    puts(is_decimal_with_precision_2(input) ? "Valid" : "Invalid");
    return 0;
}