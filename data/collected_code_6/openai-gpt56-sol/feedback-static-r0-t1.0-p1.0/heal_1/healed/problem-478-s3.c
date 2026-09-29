#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

char *remove_lowercase_substrings(const char *input, size_t length)
{
    char *result;
    size_t read_index;
    size_t write_index = 0;

    if (input == NULL || length == SIZE_MAX) {
        return NULL;
    }

    result = malloc(length + 1);
    if (result == NULL) {
        return NULL;
    }

    for (read_index = 0; read_index < length; ++read_index) {
        unsigned char character = (unsigned char)input[read_index];

        if (!islower(character)) {
            result[write_index++] = input[read_index];
        }
    }

    result[write_index] = '\0';
    return result;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;
    size_t capacity = 128;
    int character;
    char *result;

    input = malloc(capacity);
    if (input == NULL) {
        return EXIT_FAILURE;
    }

    while ((character = fgetc(stdin)) != EOF && character != '\n') {
        char *resized_input;

        if (length == capacity) {
            size_t new_capacity;

            if (capacity > SIZE_MAX / 2) {
                free(input);
                return EXIT_FAILURE;
            }

            new_capacity = capacity * 2;
            resized_input = realloc(input, new_capacity);
            if (resized_input == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = resized_input;
            capacity = new_capacity;
        }

        input[length++] = (char)character;
    }

    if (character == EOF && ferror(stdin)) {
        free(input);
        return EXIT_FAILURE;
    }

    if (character == EOF && length == 0) {
        free(input);
        return EXIT_SUCCESS;
    }

    result = remove_lowercase_substrings(input, length);
    free(input);

    if (result == NULL) {
        return EXIT_FAILURE;
    }

    if (fputs(result, stdout) == EOF || fputc('\n', stdout) == EOF) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}