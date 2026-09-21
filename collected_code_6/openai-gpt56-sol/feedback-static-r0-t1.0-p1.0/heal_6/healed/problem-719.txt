#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool matches_pattern(const char *str)
{
    if (str == NULL || *str != 'a') {
        return false;
    }

    ++str;

    while (*str == 'b') {
        ++str;
    }

    return *str == '\0';
}

int main(void)
{
    char input[1024];

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
        int character;

        do {
            character = fgetc(stdin);
        } while (character != EOF && character != '\n' && character != '\r');

        if (character == EOF && ferror(stdin)) {
            return EXIT_FAILURE;
        }

        if (fputs("No match\n", stdout) == EOF) {
            return EXIT_FAILURE;
        }

        return ferror(stdout) ? EXIT_FAILURE : EXIT_SUCCESS;
    }

    input[length] = '\0';

    if (fputs(matches_pattern(input) ? "Match\n" : "No match\n", stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return ferror(stdout) ? EXIT_FAILURE : EXIT_SUCCESS;
}