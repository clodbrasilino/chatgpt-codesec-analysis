#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

char *snake_to_camel(const char *input, size_t input_length)
{
    char *output;
    size_t read_index;
    size_t write_index = 0;
    int capitalize_next = 0;

    if (input == NULL || input_length == SIZE_MAX) {
        return NULL;
    }

    output = malloc(input_length + 1);
    if (output == NULL) {
        return NULL;
    }

    for (read_index = 0; read_index < input_length; ++read_index) {
        unsigned char character = (unsigned char)input[read_index];

        if (character == (unsigned char)'_') {
            capitalize_next = 1;
        } else if (capitalize_next) {
            output[write_index++] = (char)toupper(character);
            capitalize_next = 0;
        } else {
            output[write_index++] = (char)character;
        }
    }

    output[write_index] = '\0';
    return output;
}

int main(int argc, char **const argv)
{
    const char *input;
    char *camel_case;
    size_t input_length = 0;

    if (argc != 2) {
        if (fprintf(stderr, "Usage: %s snake_case_string\n", argv[0]) < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    input = argv[1];

    while (input[input_length] != '\0') {
        if (input_length == SIZE_MAX - 1) {
            if (fprintf(stderr, "Input is too long\n") < 0) {
                return EXIT_FAILURE;
            }
            return EXIT_FAILURE;
        }
        ++input_length;
    }

    camel_case = snake_to_camel(input, input_length);
    if (camel_case == NULL) {
        if (fprintf(stderr, "Failed to convert string\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("%s\n", camel_case) < 0) {
        free(camel_case);
        return EXIT_FAILURE;
    }

    free(camel_case);
    return EXIT_SUCCESS;
}