#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *snake_to_camel(const char *input, size_t input_size)
{
    const char *terminator;
    size_t input_len;
    size_t src;
    size_t dst = 0;
    int capitalize = 1;
    char *output;

    if (input == NULL || input_size == 0) {
        return NULL;
    }

    terminator = memchr(input, '\0', input_size);
    if (terminator == NULL) {
        return NULL;
    }

    input_len = (size_t)(terminator - input);
    if (input_len == SIZE_MAX) {
        return NULL;
    }

    output = malloc(input_len + 1);
    if (output == NULL) {
        return NULL;
    }

    for (src = 0; src < input_len; ++src) {
        unsigned char character = (unsigned char)input[src];

        if (character == (unsigned char)'_') {
            capitalize = 1;
            continue;
        }

        if (capitalize) {
            character = (unsigned char)toupper((int)character);
            capitalize = 0;
        }

        output[dst++] = (char)character;
    }

    output[dst] = '\0';
    return output;
}

int main(int argc, char *argv[])
{
    const char *program;
    const char *input;
    char *camel_case;
    size_t input_len;

    program = "program";
    if (argc > 0 && argv != NULL && argv[0] != NULL) {
        program = argv[0];
    }

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s snake_case_string\n", program);
        return EXIT_FAILURE;
    }

    input = argv[1];
    input_len = strnlen(input, SIZE_MAX);
    if (input_len == SIZE_MAX) {
        fprintf(stderr, "Input is too large or not null-terminated\n");
        return EXIT_FAILURE;
    }

    camel_case = snake_to_camel(input, input_len + 1);
    if (camel_case == NULL) {
        fprintf(stderr, "Conversion failed\n");
        return EXIT_FAILURE;
    }

    if (printf("%s\n", camel_case) < 0) {
        free(camel_case);
        return EXIT_FAILURE;
    }

    free(camel_case);
    return EXIT_SUCCESS;
}