#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

bool is_decimal_with_precision_2(const char *text)
{
    const unsigned char *p;

    if (text == NULL || *text == '\0') {
        return false;
    }

    p = (const unsigned char *)text;

    if (*p == '+' || *p == '-') {
        ++p;
    }

    if (!isdigit(*p)) {
        return false;
    }

    do {
        ++p;
    } while (isdigit(*p));

    if (*p++ != '.') {
        return false;
    }

    if (!isdigit(*p++)) {
        return false;
    }

    if (!isdigit(*p++)) {
        return false;
    }

    return *p == '\0';
}

int main(void)
{
    char input[256];

    if (fgets(input, sizeof input, stdin) == NULL) {
        puts("Invalid");
        return 1;
    }

    size_t length = 0;
    while (input[length] != '\0' &&
           input[length] != '\n' &&
           input[length] != '\r') {
        ++length;
    }

    if (input[length] == '\0' && length == sizeof input - 1) {
        int ch = getchar();

        if (ch != '\n' && ch != EOF) {
            while ((ch = getchar()) != '\n' && ch != EOF) {
            }
            puts("Invalid");
            return 1;
        }
    }

    input[length] = '\0';

    if (is_decimal_with_precision_2(input)) {
        puts("Valid");
        return 0;
    }

    puts("Invalid");
    return 1;
}