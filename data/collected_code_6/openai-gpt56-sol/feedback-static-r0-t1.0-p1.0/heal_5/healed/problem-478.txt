#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

char *remove_lowercase_substrings(const char *input, size_t length,
                                  size_t *result_length)
{
    char *result;
    size_t read_index;
    size_t write_index = 0U;

    if (input == NULL || result_length == NULL || length == SIZE_MAX) {
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
    *result_length = write_index;

    return result;
}

int main(void)
{
    char *input;
    char *result;
    size_t capacity = 128U;
    size_t length = 0U;
    size_t result_length;
    int character = EOF;

    input = malloc(capacity);
    if (input == NULL) {
        return EXIT_FAILURE;
    }

    while ((character = fgetc(stdin)) != EOF && character != '\n') {
        if (length >= capacity) {
            size_t new_capacity;
            char *new_input;

            if (capacity > SIZE_MAX / 2U) {
                free(input);
                return EXIT_FAILURE;
            }

            new_capacity = capacity * 2U;
            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)(unsigned char)character;
    }

    if (ferror(stdin) != 0) {
        free(input);
        return EXIT_FAILURE;
    }

    if (character == EOF && length == 0U) {
        free(input);
        return EXIT_SUCCESS;
    }

    result = remove_lowercase_substrings(input, length, &result_length);
    free(input);

    if (result == NULL) {
        return EXIT_FAILURE;
    }

    if (result_length != 0U &&
        fwrite(result, sizeof(*result), result_length, stdout) != result_length) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);

    if (fputc('\n', stdout) == EOF || fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}