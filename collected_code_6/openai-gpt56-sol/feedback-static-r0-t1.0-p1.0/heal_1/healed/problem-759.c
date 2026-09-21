#include <ctype.h>
#include <stdbool.h>
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

    while (isdigit(*p)) {
        ++integer_digits;
        ++p;
    }

    if (integer_digits == 0 || *p != '.') {
        return false;
    }

    ++p;

    if (!isdigit(*p)) {
        return false;
    }
    ++p;

    if (!isdigit(*p)) {
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

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length + 1 >= sizeof input) {
            do {
                ch = fgetc(stdin);
            } while (ch != '\n' && ch != EOF);

            if (ferror(stdin)) {
                return 1;
            }

            puts("Invalid");
            return 0;
        }

        input[length++] = (char)ch;
    }

    if (ferror(stdin)) {
        return 1;
    }

    if (ch == EOF && length == 0) {
        return 0;
    }

    input[length] = '\0';

    puts(is_decimal_with_precision_2(input) ? "Valid" : "Invalid");
    return 0;
}