#include <stdbool.h>
#include <stdio.h>

enum { INPUT_CAPACITY = 1024 };

static bool all_characters_same(const char *str, size_t length)
{
    if (str == NULL || length == 0) {
        return false;
    }

    for (size_t i = 1; i < length; ++i) {
        if (str[i] != str[0]) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    char input[INPUT_CAPACITY];
    size_t length = 0;
    int ch;

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length >= sizeof input) {
            while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
            }

            if (ferror(stdin)) {
                fputs("Failed to read input.\n", stderr);
            } else {
                fputs("Input is too long.\n", stderr);
            }

            return 1;
        }

        input[length++] = (char)ch;
    }

    if (ferror(stdin)) {
        fputs("Failed to read input.\n", stderr);
        return 1;
    }

    if (ch == EOF && length == 0) {
        fputs("No input provided.\n", stderr);
        return 1;
    }

    if (length > 0 && input[length - 1] == '\r') {
        --length;
    }

    if (all_characters_same(input, length)) {
        puts("All characters are the same.");
    } else {
        puts("Not all characters are the same.");
    }

    return 0;
}