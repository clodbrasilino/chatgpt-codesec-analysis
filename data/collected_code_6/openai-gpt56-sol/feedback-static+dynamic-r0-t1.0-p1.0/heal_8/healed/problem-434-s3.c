#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool matches(const char *str)
{
    if (str == NULL || str[0] != 'a' || str[1] != 'b') {
        return false;
    }

    str += 2;

    while (*str == 'b') {
        ++str;
    }

    return *str == '\0';
}

int main(void)
{
    char input[4096];

    if (fgets(input, sizeof input, stdin) == NULL) {
        return ferror(stdin) ? EXIT_FAILURE : EXIT_SUCCESS;
    }

    size_t length = 0;

    while (input[length] != '\0' &&
           input[length] != '\n' &&
           input[length] != '\r') {
        ++length;
    }

    if (input[length] == '\0' && length == sizeof input - 1) {
        int ch;

        do {
            ch = fgetc(stdin);
        } while (ch != EOF && ch != '\n' && ch != '\r');

        if (ferror(stdin)) {
            return EXIT_FAILURE;
        }

        if (ch != '\n' && ch != '\r') {
            return EXIT_FAILURE;
        }
    }

    input[length] = '\0';

    return puts(matches(input) ? "Match" : "No match") == EOF
               ? EXIT_FAILURE
               : EXIT_SUCCESS;
}