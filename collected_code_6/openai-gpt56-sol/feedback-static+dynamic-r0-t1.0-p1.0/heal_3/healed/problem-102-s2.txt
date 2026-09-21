#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *snake_to_camel(const char *input)
{
    size_t length;
    size_t output_index = 0;
    int capitalize = 1;
    char *output;

    if (input == NULL) {
        return NULL;
    }

    length = strlen(input);

    if (length == SIZE_MAX) {
        return NULL;
    }

    output = malloc(length + 1);
    if (output == NULL) {
        return NULL;
    }

    for (size_t input_index = 0; input_index < length; ++input_index) {
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
    size_t capacity = 0;
    size_t length = 0;
    int character;

    while ((character = getchar()) != '\n' && character != EOF) {
        if (character == '\r') {
            continue;
        }

        if (length == SIZE_MAX - 1) {
            free(input);
            return EXIT_FAILURE;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity = capacity == 0 ? 128 : capacity * 2;

            if (new_capacity <= capacity || new_capacity > SIZE_MAX) {
                free(input);
                return EXIT_FAILURE;
            }

            char *resized = realloc(input, new_capacity);
            if (resized == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)character;
    }

    if (character == EOF && length == 0) {
        free(input);
        return EXIT_FAILURE;
    }

    if (length + 1 > capacity) {
        char *resized = realloc(input, length + 1);
        if (resized == NULL) {
            free(input);
            return EXIT_FAILURE;
        }
        input = resized;
    }

    input[length] = '\0';

    char *output = snake_to_camel(input);
    free(input);

    if (output == NULL) {
        return EXIT_FAILURE;
    }

    if (printf("%s\n", output) < 0) {
        free(output);
        return EXIT_FAILURE;
    }

    free(output);
    return EXIT_SUCCESS;
}