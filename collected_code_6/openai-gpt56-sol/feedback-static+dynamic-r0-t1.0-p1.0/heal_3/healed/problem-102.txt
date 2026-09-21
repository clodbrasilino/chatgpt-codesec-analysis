#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *snake_to_camel(const char *input)
{
    size_t length;
    size_t read_index;
    size_t write_index = 0;
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

    for (read_index = 0; read_index < length; ++read_index) {
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

int main(int argc, char *argv[])
{
    char *result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s snake_case_string\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    result = snake_to_camel(argv[1]);
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