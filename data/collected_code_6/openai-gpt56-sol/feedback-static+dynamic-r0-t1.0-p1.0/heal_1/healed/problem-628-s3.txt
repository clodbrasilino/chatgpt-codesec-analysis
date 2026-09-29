#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

char *replace_spaces(const char *input, size_t length)
{
    size_t spaces = 0;

    if (input == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < length; ++i) {
        if (input[i] == ' ') {
            ++spaces;
        }
    }

    if (spaces > (SIZE_MAX - length - 1) / 2) {
        return NULL;
    }

    size_t output_length = length + spaces * 2;
    char *output = malloc(output_length + 1);

    if (output == NULL) {
        return NULL;
    }

    char *destination = output;

    for (size_t i = 0; i < length; ++i) {
        if (input[i] == ' ') {
            *destination++ = '%';
            *destination++ = '2';
            *destination++ = '0';
        } else {
            *destination++ = input[i];
        }
    }

    *destination = '\0';
    return output;
}

int main(void)
{
    size_t capacity = 128;
    size_t length = 0;
    char *input = malloc(capacity);

    if (input == NULL) {
        fprintf(stderr, "Failed to allocate input buffer.\n");
        return EXIT_FAILURE;
    }

    int character;

    while ((character = fgetc(stdin)) != EOF && character != '\n') {
        if (length == SIZE_MAX - 1) {
            fprintf(stderr, "Input is too long.\n");
            free(input);
            return EXIT_FAILURE;
        }

        if (length + 1 >= capacity) {
            if (capacity > SIZE_MAX / 2) {
                fprintf(stderr, "Input is too long.\n");
                free(input);
                return EXIT_FAILURE;
            }

            size_t new_capacity = capacity * 2;
            char *new_input = realloc(input, new_capacity);

            if (new_input == NULL) {
                fprintf(stderr, "Failed to allocate input buffer.\n");
                free(input);
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)character;
    }

    if (ferror(stdin)) {
        fprintf(stderr, "Failed to read input.\n");
        free(input);
        return EXIT_FAILURE;
    }

    if (character == EOF && length == 0) {
        free(input);
        return EXIT_SUCCESS;
    }

    input[length] = '\0';

    char *result = replace_spaces(input, length);
    free(input);

    if (result == NULL) {
        fprintf(stderr, "Failed to replace spaces.\n");
        return EXIT_FAILURE;
    }

    if (puts(result) == EOF) {
        fprintf(stderr, "Failed to write output.\n");
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}