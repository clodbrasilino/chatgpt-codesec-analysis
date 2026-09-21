#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *snake_to_camel(const char *input)
{
    const char *end;
    size_t length;
    size_t read_index;
    size_t write_index = 0;
    int capitalize = 0;
    char *output;

    if (input == NULL) {
        return NULL;
    }

    end = memchr(input, '\0', SIZE_MAX);
    if (end == NULL) {
        return NULL;
    }

    length = (size_t)(end - input);
    output = malloc(length + 1);
    if (output == NULL) {
        return NULL;
    }

    for (read_index = 0; read_index < length; ++read_index) {
        unsigned char character = (unsigned char)input[read_index];

        if (character == '_') {
            capitalize = 1;
        } else if (capitalize) {
            output[write_index++] = (char)toupper(character);
            capitalize = 0;
        } else {
            output[write_index++] = (char)character;
        }
    }

    output[write_index] = '\0';
    return output;
}

int main(int argc, char *const argv[])
{
    char *result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s snake_case_string\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    result = snake_to_camel(argv[1]);
    if (result == NULL) {
        fputs("Failed to convert string\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%s\n", result) < 0) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}