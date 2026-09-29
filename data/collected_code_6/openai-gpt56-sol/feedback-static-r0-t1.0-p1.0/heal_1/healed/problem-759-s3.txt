#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

bool is_decimal_with_precision_2(const char *text)
{
    const unsigned char *p = (const unsigned char *)text;
    size_t integer_digits = 0;

    if (text == NULL || *p == '\0') {
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

    if (!isdigit(p[0])) {
        return false;
    }

    ++p;

    if (!isdigit(p[0])) {
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

    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (length + 1 >= sizeof input) {
            while ((ch = getchar()) != '\n' && ch != EOF) {
            }
            puts("Invalid");
            return 1;
        }

        input[length++] = (char)ch;
    }

    if (length > 0 && input[length - 1] == '\r') {
        --length;
    }

    input[length] = '\0';

    if (is_decimal_with_precision_2(input)) {
        puts("Valid");
        return 0;
    }

    puts("Invalid");
    return 1;
}