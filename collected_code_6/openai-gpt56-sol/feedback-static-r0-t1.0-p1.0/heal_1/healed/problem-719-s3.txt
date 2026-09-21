#include <stdbool.h>
#include <stdio.h>

static bool matches_pattern(const char *str)
{
    if (str == NULL || *str++ != 'a') {
        return false;
    }

    while (*str == 'b') {
        ++str;
    }

    return *str == '\0';
}

int main(void)
{
    enum { INPUT_SIZE = 1024 };
    char input[INPUT_SIZE];

    if (fgets(input, sizeof input, stdin) == NULL) {
        return ferror(stdin) ? 1 : 0;
    }

    size_t length = 0;

    while (length < sizeof input &&
           input[length] != '\0' &&
           input[length] != '\n' &&
           input[length] != '\r') {
        ++length;
    }

    if (length == sizeof input) {
        return 1;
    }

    if (input[length] == '\0' && length == sizeof input - 1) {
        int ch;

        while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        }

        return 1;
    }

    input[length] = '\0';

    if (input[length + 1] == '\n' && input[length] == '\r') {
        input[length + 1] = '\0';
    }

    puts(matches_pattern(input) ? "Match" : "No match");
    return 0;
}