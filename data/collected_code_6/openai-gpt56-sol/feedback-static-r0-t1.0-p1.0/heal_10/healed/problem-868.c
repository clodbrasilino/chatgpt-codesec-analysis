#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static size_t length_of_last_word(const char *string)
{
    size_t current_length = 0;
    size_t last_length = 0;

    if (string == NULL) {
        return 0;
    }

    while (*string != '\0') {
        if (isspace((unsigned char)*string)) {
            if (current_length != 0) {
                last_length = current_length;
                current_length = 0;
            }
        } else {
            ++current_length;
        }

        ++string;
    }

    return current_length != 0 ? current_length : last_length;
}

int main(void)
{
    size_t capacity = 128;
    size_t length = 0;
    char *input = malloc(capacity);

    if (input == NULL) {
        fputs("Failed to allocate memory.\n", stderr);
        return EXIT_FAILURE;
    }

    for (;;) {
        int character;

        if (length == capacity - 1) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2) {
                fputs("Input is too large.\n", stderr);
                free(input);
                return EXIT_FAILURE;
            }

            new_capacity = capacity * 2;
            resized = realloc(input, new_capacity);

            if (resized == NULL) {
                fputs("Failed to allocate memory.\n", stderr);
                free(input);
                return EXIT_FAILURE;
            }

            input = resized;
            capacity = new_capacity;
        }

        character = fgetc(stdin);

        if (character == EOF) {
            if (ferror(stdin)) {
                fputs("Failed to read input.\n", stderr);
                free(input);
                return EXIT_FAILURE;
            }
            break;
        }

        if (character == '\n') {
            break;
        }

        input[length++] = (char)(unsigned char)character;
    }

    input[length] = '\0';

    if (printf("%zu\n", length_of_last_word(input)) < 0) {
        fputs("Failed to write output.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}