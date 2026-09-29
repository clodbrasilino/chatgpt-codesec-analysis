#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static char *snake_to_camel(const char *input, size_t input_length)
{
    if (input == NULL || input_length == SIZE_MAX) {
        return NULL;
    }

    char *output = malloc(input_length + 1);
    if (output == NULL) {
        return NULL;
    }

    size_t output_index = 0;
    int capitalize = 1;

    for (size_t input_index = 0; input_index < input_length; ++input_index) {
        unsigned char character = (unsigned char)input[input_index];

        if (character == '_') {
            capitalize = 1;
            continue;
        }

        if (capitalize) {
            character = (unsigned char)toupper(character);
            capitalize = 0;
        }

        output[output_index++] = (char)character;
    }

    output[output_index] = '\0';
    return output;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int character = EOF;

    while ((character = getchar()) != EOF && character != '\n') {
        if (character == '\r') {
            continue;
        }

        if (length == SIZE_MAX - 1) {
            free(input);
            return EXIT_FAILURE;
        }

        if (length == capacity) {
            size_t new_capacity;

            if (capacity == 0) {
                new_capacity = 128;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(input);
                    return EXIT_FAILURE;
                }
                new_capacity = capacity * 2;
            }

            char *resized = realloc(input, new_capacity);
            if (resized == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)(unsigned char)character;
    }

    if (character == EOF && length == 0) {
        free(input);
        return EXIT_FAILURE;
    }

    char *output = snake_to_camel(input, length);
    free(input);

    if (output == NULL) {
        return EXIT_FAILURE;
    }

    if (fputs(output, stdout) == EOF || fputc('\n', stdout) == EOF) {
        free(output);
        return EXIT_FAILURE;
    }

    free(output);
    return EXIT_SUCCESS;
}