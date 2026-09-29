#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static char *replace_spaces(const char *input, size_t length)
{
    if (input == NULL && length != 0U) {
        return NULL;
    }

    size_t spaces = 0U;

    for (size_t i = 0U; i < length; ++i) {
        if (input[i] == ' ') {
            ++spaces;
        }
    }

    if (length > SIZE_MAX - 1U ||
        spaces > (SIZE_MAX - length - 1U) / 2U) {
        return NULL;
    }

    size_t output_length = length + spaces * 2U;
    char *output = malloc(output_length + 1U);

    if (output == NULL) {
        return NULL;
    }

    size_t destination = 0U;

    for (size_t i = 0U; i < length; ++i) {
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
    char *input = NULL;
    size_t length = 0U;
    size_t capacity = 0U;
    int character;

    while ((character = fgetc(stdin)) != EOF && character != '\n') {
        if (length == capacity) {
            size_t new_capacity;

            if (capacity == 0U) {
                new_capacity = 128U;
            } else {
                if (capacity > SIZE_MAX / 2U) {
                    free(input);
                    fputs("Input is too long.\n", stderr);
                    return EXIT_FAILURE;
                }

                new_capacity = capacity * 2U;
            }

            if (new_capacity <= length) {
                free(input);
                fputs("Input is too long.\n", stderr);
                return EXIT_FAILURE;
            }

            char *new_input = realloc(input, new_capacity);

            if (new_input == NULL) {
                free(input);
                fputs("Failed to allocate memory.\n", stderr);
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)(unsigned char)character;
    }

    if (ferror(stdin)) {
        free(input);
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (character == EOF && length == 0U) {
        free(input);
        return EXIT_SUCCESS;
    }

    char *result = replace_spaces(input, length);
    free(input);

    if (result == NULL) {
        fputs("Failed to replace spaces.\n", stderr);
        return EXIT_FAILURE;
    }

    if (fputs(result, stdout) == EOF || fputc('\n', stdout) == EOF) {
        free(result);
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}