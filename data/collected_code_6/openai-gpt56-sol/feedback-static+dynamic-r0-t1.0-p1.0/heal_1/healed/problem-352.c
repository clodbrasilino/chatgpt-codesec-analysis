#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool all_characters_unique(const char *str)
{
    bool seen[256] = { false };

    if (str == NULL) {
        return false;
    }

    while (*str != '\0') {
        unsigned char character = (unsigned char)*str;

        if (seen[character]) {
            return false;
        }

        seen[character] = true;
        ++str;
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
        if (length + 1 >= capacity) {
            size_t new_capacity = capacity == 0 ? 128 : capacity * 2;

            if (new_capacity <= capacity) {
                free(input);
                fputs("Input is too long.\n", stderr);
                return 1;
            }

            char *new_input = realloc(input, new_capacity);

            if (new_input == NULL) {
                free(input);
                fputs("Failed to allocate memory.\n", stderr);
                return 1;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ferror(stdin)) {
        free(input);
        fputs("Failed to read input.\n", stderr);
        return 1;
    }

    if (input == NULL) {
        input = malloc(1);

        if (input == NULL) {
            fputs("Failed to allocate memory.\n", stderr);
            return 1;
        }
    }

    input[length] = '\0';

    printf("%s\n", all_characters_unique(input) ? "true" : "false");

    free(input);
    return 0;
}