#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

char *snake_to_camel(const char *input, size_t input_length)
{
    char *output;
    size_t read_index;
    size_t write_index = 0;
    int capitalize_next = 1;

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
            continue;
        }

        if (capitalize_next) {
            output[write_index++] = (char)toupper(character);
            capitalize_next = 0;
        } else {
            output[write_index++] = (char)character;
        }
    }

    output[write_index] = '\0';
    return output;
}

int main(int argc, char **argv)
{
    const char *program_name;
    size_t input_length = 0;
    char *camel_case;

    program_name = argc > 0 && argv != NULL && argv[0] != NULL
                       ? argv[0]
                       : "program";

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        if (fprintf(stderr, "Usage: %s snake_case_string\n", program_name) < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    while (argv[1][input_length] != '\0') {
        if (input_length == SIZE_MAX - 1) {
            if (fputs("Input is too long\n", stderr) == EOF) {
                return EXIT_FAILURE;
            }
            return EXIT_FAILURE;
        }
        ++input_length;
    }

    camel_case = snake_to_camel(argv[1], input_length);
    if (camel_case == NULL) {
        if (fputs("Conversion failed\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (fputs(camel_case, stdout) == EOF || fputc('\n', stdout) == EOF) {
        free(camel_case);
        return EXIT_FAILURE;
    }

    free(camel_case);
    return EXIT_SUCCESS;
}