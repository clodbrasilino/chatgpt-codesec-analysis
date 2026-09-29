#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool has_letter_and_number(const char *str)
{
    bool has_letter = false;
    bool has_number = false;

    if (str == NULL) {
        return false;
    }

    while (*str != '\0') {
        unsigned char character = (unsigned char)*str++;

        if (isalpha(character) != 0) {
            has_letter = true;
        }

        if (isdigit(character) != 0) {
            has_number = true;
        }

        if (has_letter && has_number) {
            return true;
        }
    }

    return false;
}

static char *read_line(FILE *stream)
{
    size_t length = 0;
    size_t capacity = 128;
    char *input;

    if (stream == NULL) {
        return NULL;
    }

    input = malloc(capacity);
    if (input == NULL) {
        return NULL;
    }

    for (;;) {
        int character;

        if (length == capacity - 1) {
            size_t new_capacity;
            char *new_input;

            if (capacity > SIZE_MAX / 2) {
                free(input);
                return NULL;
            }

            new_capacity = capacity * 2;
            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                return NULL;
            }

            input = new_input;
            capacity = new_capacity;
        }

        character = fgetc(stream);

        if (character == EOF) {
            if (ferror(stream) != 0 || length == 0) {
                free(input);
                return NULL;
            }
            break;
        }

        if (character == '\n') {
            break;
        }

        if (character == '\r') {
            int next_character = fgetc(stream);

            if (next_character != '\n' && next_character != EOF) {
                if (ungetc(next_character, stream) == EOF) {
                    free(input);
                    return NULL;
                }
            } else if (next_character == EOF && ferror(stream) != 0) {
                free(input);
                return NULL;
            }

            break;
        }

        input[length++] = (char)character;
    }

    input[length] = '\0';
    return input;
}

int main(void)
{
    char *input = read_line(stdin);

    if (input == NULL) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (has_letter_and_number(input)) {
        puts("The string contains at least one letter and one number.");
    } else {
        puts("The string does not contain at least one letter and one number.");
    }

    free(input);
    return EXIT_SUCCESS;
}