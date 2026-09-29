#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

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
    char *input = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int character;

    for (;;) {
        character = fgetc(stdin);

        if (character == EOF || character == '\n' || character == '\r') {
            break;
        }

        if (length == SIZE_MAX - 1) {
            free(input);
            return EXIT_FAILURE;
        }

        if (length + 1 >= capacity) {
            size_t required = length + 2;
            size_t new_capacity;

            if (capacity == 0) {
                new_capacity = 128;
            } else if (capacity > SIZE_MAX / 2) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2;
            }

            if (new_capacity < required) {
                new_capacity = required;
            }

            char *new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)character;
    }

    if (character == EOF && ferror(stdin)) {
        free(input);
        return EXIT_FAILURE;
    }

    if (input == NULL) {
        input = malloc(1);
        if (input == NULL) {
            return EXIT_FAILURE;
        }
    }

    input[length] = '\0';

    if (matches_pattern(input)) {
        if (fputs("Match\n", stdout) == EOF) {
            free(input);
            return EXIT_FAILURE;
        }
    } else {
        if (fputs("No match\n", stdout) == EOF) {
            free(input);
            return EXIT_FAILURE;
        }
    }

    free(input);

    if (fflush(stdout) == EOF || ferror(stdout)) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}