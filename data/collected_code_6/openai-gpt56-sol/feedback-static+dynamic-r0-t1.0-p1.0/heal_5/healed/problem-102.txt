#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

char *snake_to_camel(const char *input, size_t input_length)
{
    size_t read_index;
    size_t write_index = 0;
    int capitalize = 1;
    char *output;

    if (input == NULL || input_length == SIZE_MAX) {
        return NULL;
    }

    output = malloc(input_length + 1);
    if (output == NULL) {
        return NULL;
    }

    for (read_index = 0; read_index < input_length; ++read_index) {
        unsigned char character = (unsigned char)input[read_index];

        if (character == '_') {
            capitalize = 1;
        } else {
            output[write_index++] = capitalize
                ? (char)toupper(character)
                : (char)character;
            capitalize = 0;
        }
    }

    output[write_index] = '\0';
    return output;
}

int main(int argc, char *const argv[])
{
    const char *input;
    size_t input_length = 0;
    char *result;

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        const char *program =
            argv != NULL && argc > 0 && argv[0] != NULL ? argv[0] : "program";

        fprintf(stderr, "Usage: %s snake_case_string\n", program);
        return EXIT_FAILURE;
    }

    input = argv[1];

    while (input[input_length] != '\0') {
        if (input_length == SIZE_MAX - 1) {
            fprintf(stderr, "Input is too long\n");
            return EXIT_FAILURE;
        }
        ++input_length;
    }

    result = snake_to_camel(input, input_length);
    if (result == NULL) {
        fprintf(stderr, "Failed to convert string\n");
        return EXIT_FAILURE;
    }

    if (puts(result) == EOF) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}