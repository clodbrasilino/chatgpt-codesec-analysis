#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_SIZE 4096

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

    do {
        ++p;
    } while (isdigit(*p));

    if (*p++ != '.') {
        return false;
    }

    if (!isdigit(p[0]) || !isdigit(p[1])) {
        return false;
    }

    return p[2] == '\0';
}

int main(void)
{
    char input[INPUT_SIZE];

    if (fgets(input, sizeof input, stdin) == NULL) {
        puts("Invalid");
        return EXIT_FAILURE;
    }

    size_t length = 0;

    while (input[length] != '\0' &&
           input[length] != '\n' &&
           input[length] != '\r') {
        ++length;
    }

    if (input[length] == '\0' && length == sizeof input - 1) {
        int ch = getchar();

        if (ch != '\n' && ch != '\r' && ch != EOF) {
            puts("Invalid");
            return EXIT_FAILURE;
        }

        if (ch == EOF && ferror(stdin)) {
            puts("Invalid");
            return EXIT_FAILURE;
        }
    }

    input[length] = '\0';

    bool valid = is_decimal_with_precision_2(input);
    puts(valid ? "Valid" : "Invalid");

    return valid ? EXIT_SUCCESS : EXIT_FAILURE;
}