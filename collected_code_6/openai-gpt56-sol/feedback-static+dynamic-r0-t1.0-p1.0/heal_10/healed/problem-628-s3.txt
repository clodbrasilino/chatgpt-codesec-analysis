#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

char *replace_spaces(const char *input, size_t length)
{
    if (input == NULL) {
        return NULL;
    }

    size_t spaces = 0;

    for (size_t i = 0; i < length; ++i) {
        if (input[i] == ' ') {
            ++spaces;
        }
    }

    if (length > SIZE_MAX - 1 ||
        spaces > (SIZE_MAX - length - 1) / 2) {
        return NULL;
    }

    size_t output_length = length + spaces * 2;
    char *output = malloc(output_length + 1);

    if (output == NULL) {
        return NULL;
    }

    size_t destination = 0;

    for (size_t i = 0; i < length; ++i) {
        if (input[i] == ' ') {
            output[destination++] = '%';
            output[destination++] = '2';
            output[destination++] = '0';
        } else {
            output[destination++] = input[i];
        }
    }

    output[destination] = '\0';
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

    for (;;) {
        int character = fgetc(stdin);

        if (character == EOF) {
            if (ferror(stdin)) {
                fprintf(stderr, "Failed to read input.\n");
                free(input);
                return EXIT_FAILURE;
            }
            break;
        }

        if (character == '\n') {
            break;
        }

        if (length >= capacity - 1) {
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

        input[length++] = (char)(unsigned char)character;
    }

    if (length == 0 && feof(stdin)) {
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

    if (fputs(result, stdout) == EOF || fputc('\n', stdout) == EOF) {
        fprintf(stderr, "Failed to write output.\n");
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}