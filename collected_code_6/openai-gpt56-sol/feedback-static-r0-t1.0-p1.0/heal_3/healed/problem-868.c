#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

size_t length_of_last_word(const char *string)
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
    char *input;
    size_t length = 0;
    size_t capacity = 128;
    int character;

    input = malloc(capacity);
    if (input == NULL) {
        fputs("Failed to allocate memory.\n", stderr);
        return EXIT_FAILURE;
    }

    while ((character = getchar()) != '\n' && character != EOF) {
        if (length > SIZE_MAX - 2) {
            free(input);
            fputs("Input is too large.\n", stderr);
            return EXIT_FAILURE;
        }

        if (length + 1 >= capacity) {
            size_t required = length + 2;
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2;
            }

            if (new_capacity < required) {
                new_capacity = required;
            }

            resized = realloc(input, new_capacity);
            if (resized == NULL) {
                free(input);
                fputs("Failed to allocate memory.\n", stderr);
                return EXIT_FAILURE;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)character;
    }

    if (character == EOF && ferror(stdin)) {
        free(input);
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    input[length] = '\0';

    if (printf("%zu\n", length_of_last_word(input)) < 0) {
        free(input);
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}