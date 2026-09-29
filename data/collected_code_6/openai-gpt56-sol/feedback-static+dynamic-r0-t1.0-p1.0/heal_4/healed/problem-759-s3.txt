#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool is_decimal_with_precision_2(const char *text)
{
    const unsigned char *p = (const unsigned char *)text;
    size_t integer_digits = 0;

    if (text == NULL || *text == '\0') {
        return false;
    }

    if (*p == '+' || *p == '-') {
        ++p;
    }

    while (isdigit((unsigned char)*p)) {
        ++integer_digits;
        ++p;
    }

    if (integer_digits == 0 || *p != '.') {
        return false;
    }

    ++p;

    if (!isdigit((unsigned char)p[0]) ||
        !isdigit((unsigned char)p[1]) ||
        p[2] != '\0') {
        return false;
    }

    return true;
}

int main(void)
{
    char input[4096];

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    size_t length = strlen(input);

    if (length > 0 && input[length - 1] == '\n') {
        input[--length] = '\0';

        if (length > 0 && input[length - 1] == '\r') {
            input[--length] = '\0';
        }
    } else if (!feof(stdin)) {
        int ch;

        do {
            ch = getchar();
        } while (ch != '\n' && ch != EOF);

        return EXIT_FAILURE;
    }

    if (is_decimal_with_precision_2(input)) {
        puts("Valid");
        return EXIT_SUCCESS;
    }

    puts("Invalid");
    return EXIT_FAILURE;
}