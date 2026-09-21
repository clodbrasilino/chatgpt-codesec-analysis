#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool is_decimal_with_precision_2(const char *text)
{
    if (text == NULL || *text == '\0') {
        return false;
    }

    const unsigned char *p = (const unsigned char *)text;

    if (*p == '+' || *p == '-') {
        ++p;
    }

    if (!isdigit(*p)) {
        return false;
    }

    while (isdigit(*p)) {
        ++p;
    }

    if (*p != '.') {
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
    enum { INPUT_SIZE = 4096 };
    char input[INPUT_SIZE];

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    size_t length = 0;
    while (input[length] != '\0' && input[length] != '\n' &&
           input[length] != '\r') {
        ++length;
    }

    if (input[length] == '\0' && !feof(stdin)) {
        int ch;
        while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        }
        return EXIT_FAILURE;
    }

    input[length] = '\0';

    bool valid = is_decimal_with_precision_2(input);
    puts(valid ? "Valid" : "Invalid");

    return valid ? EXIT_SUCCESS : EXIT_FAILURE;
}