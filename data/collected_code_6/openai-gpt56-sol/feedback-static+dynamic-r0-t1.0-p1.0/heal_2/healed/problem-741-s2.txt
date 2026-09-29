#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool all_characters_same(const char *string)
{
    if (string == NULL || string[0] == '\0') {
        return false;
    }

    for (size_t i = 1; string[i] != '\0'; ++i) {
        if (string[i] != string[0]) {
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
    int character;

    while ((character = fgetc(stdin)) != '\n' && character != EOF) {
        if (length == capacity) {
            size_t new_capacity = capacity == 0 ? 128 : capacity * 2;

            if (new_capacity <= capacity || new_capacity > SIZE_MAX / sizeof *input) {
                free(input);
                fputs("Input is too long.\n", stderr);
                return 1;
            }

            char *resized = realloc(input, new_capacity * sizeof *input);
            if (resized == NULL) {
                free(input);
                fputs("Failed to allocate memory.\n", stderr);
                return 1;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)character;
    }

    if (character == EOF && ferror(stdin)) {
        free(input);
        fputs("Failed to read input.\n", stderr);
        return 1;
    }

    if (length == capacity) {
        size_t new_capacity = capacity == 0 ? 1 : capacity + 1;

        if (new_capacity <= capacity) {
            free(input);
            fputs("Input is too long.\n", stderr);
            return 1;
        }

        char *resized = realloc(input, new_capacity * sizeof *input);
        if (resized == NULL) {
            free(input);
            fputs("Failed to allocate memory.\n", stderr);
            return 1;
        }

        input = resized;
        capacity = new_capacity;
    }

    input[length] = '\0';

    puts(all_characters_same(input)
             ? "All characters are the same."
             : "Not all characters are the same.");

    free(input);
    return 0;
}