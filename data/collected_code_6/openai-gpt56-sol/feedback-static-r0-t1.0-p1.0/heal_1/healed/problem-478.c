#include <ctype.h>
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
    char *input = NULL;
    char *result;
    size_t capacity = 0U;
    size_t length = 0U;
    int character;

    while ((character = fgetc(stdin)) != EOF && character != '\n') {
        if (length == capacity) {
            size_t new_capacity;
            char *new_input;

            if (capacity == 0U) {
                new_capacity = 128U;
            } else {
                if (capacity > (SIZE_MAX - 1U) / 2U) {
                    free(input);
                    return EXIT_FAILURE;
                }
                new_capacity = capacity * 2U;
            }

            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)character;
    }

    if (ferror(stdin) != 0) {
        free(input);
        return EXIT_FAILURE;
    }

    if (character == EOF && length == 0U) {
        free(input);
        return EXIT_SUCCESS;
    }

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