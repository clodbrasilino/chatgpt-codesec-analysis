#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

char *remove_character(const char *input, size_t input_length,
                       unsigned char character)
{
    size_t output_length = 0;
    size_t i;
    size_t j = 0;
    char *output;

    if (input == NULL && input_length != 0) {
        return NULL;
    }

    for (i = 0; i < input_length; ++i) {
        if ((unsigned char)input[i] != character) {
            ++output_length;
        }
    }

    if (output_length == SIZE_MAX) {
        return NULL;
    }

    output = malloc(output_length + 1);
    if (output == NULL) {
        return NULL;
    }

    for (i = 0; i < input_length; ++i) {
        if ((unsigned char)input[i] != character) {
            output[j++] = input[i];
        }
    }

    output[j] = '\0';
    return output;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t input_length = 0;
    int value;
    int character;
    char *result;

    for (;;) {
        value = getchar();

        if (value == '\n' || value == EOF) {
            break;
        }

        if (input_length == capacity) {
            size_t new_capacity;
            char *new_input;

            if (capacity == 0) {
                new_capacity = 128;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(input);
                    return EXIT_FAILURE;
                }
                new_capacity = capacity * 2;
            }

            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[input_length++] = (char)(unsigned char)value;
    }

    if (value == EOF && input_length == 0) {
        free(input);
        return EXIT_FAILURE;
    }

    for (;;) {
        character = getchar();

        if (character == EOF) {
            free(input);
            return EXIT_FAILURE;
        }

        if (character != ' ' && character != '\t' &&
            character != '\n' && character != '\r' &&
            character != '\f' && character != '\v') {
            break;
        }
    }

    result = remove_character(input, input_length,
                              (unsigned char)character);
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