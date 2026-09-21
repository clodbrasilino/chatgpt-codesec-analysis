#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

char *remove_lowercase_substrings(const char *input, size_t length)
{
    char *result;
    size_t read_index;
    size_t write_index = 0U;

    if (input == NULL || length == SIZE_MAX) {
        return NULL;
    }

    result = malloc(length + 1U);
    if (result == NULL) {
        return NULL;
    }

    for (read_index = 0U; read_index < length; ++read_index) {
        unsigned char character = (unsigned char)input[read_index];

        if (islower(character) == 0) {
            result[write_index++] = input[read_index];
        }
    }

    result[write_index] = '\0';
    return result;
}

int main(void)
{
    char *input;
    char *result;
    size_t capacity = 128U;
    size_t length = 0U;
    int character;

    input = malloc(capacity);
    if (input == NULL) {
        return EXIT_FAILURE;
    }

    while ((character = fgetc(stdin)) != EOF && character != '\n') {
        if (length >= capacity - 1U) {
            size_t new_capacity;
            char *resized_input;

            if (capacity > SIZE_MAX / 2U) {
                free(input);
                return EXIT_FAILURE;
            }

            new_capacity = capacity * 2U;
            resized_input = realloc(input, new_capacity);
            if (resized_input == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = resized_input;
            capacity = new_capacity;
        }

        input[length++] = (char)(unsigned char)character;
    }

    if (character == EOF && ferror(stdin) != 0) {
        free(input);
        return EXIT_FAILURE;
    }

    input[length] = '\0';

    result = remove_lowercase_substrings(input, length);
    free(input);

    if (result == NULL) {
        return EXIT_FAILURE;
    }

    if (puts(result) == EOF) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}