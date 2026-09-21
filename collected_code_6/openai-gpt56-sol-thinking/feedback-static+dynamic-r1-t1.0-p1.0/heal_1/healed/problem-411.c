#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *snake_to_camel(const char *input)
{
    char *output;
    size_t input_length;
    size_t read_index;
    size_t write_index = 0;
    int capitalize_next = 1;

    if (input == NULL) {
        return NULL;
    }

    input_length = strlen(input);
    if (input_length == SIZE_MAX) {
        return NULL;
    }

    output = malloc(input_length + 1);
    if (output == NULL) {
        return NULL;
    }

    for (read_index = 0; read_index < input_length; ++read_index) {
        unsigned char character = (unsigned char)input[read_index];

        if (character == '_') {
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
    char *camel_case;

    if (argc != 2) {
        if (fprintf(stderr, "Usage: %s snake_case_string\n", argv[0]) < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    camel_case = snake_to_camel(argv[1]);
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