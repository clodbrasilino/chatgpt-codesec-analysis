#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

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
    char *input = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int ch;

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length == capacity) {
            size_t new_capacity = capacity == 0 ? 128 : capacity * 2;

            if (new_capacity <= capacity) {
                fputs("Input is too large.\n", stderr);
                free(input);
                return 1;
            }

            char *new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                fputs("Unable to allocate memory.\n", stderr);
                free(input);
                return 1;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ferror(stdin)) {
        fputs("Failed to read input.\n", stderr);
        free(input);
        return 1;
    }

    if (ch == EOF && length == 0) {
        fputs("No input provided.\n", stderr);
        free(input);
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

    free(input);
    return 0;
}