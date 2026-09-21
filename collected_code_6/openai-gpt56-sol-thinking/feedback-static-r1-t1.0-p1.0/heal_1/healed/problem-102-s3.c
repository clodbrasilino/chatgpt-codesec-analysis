#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

char *snake_to_camel(const char *input, size_t input_length)
{
    size_t source_index;
    size_t destination_index = 0;
    int capitalize_next = 0;
    char *result;

    if (input == NULL || input_length == SIZE_MAX) {
        return NULL;
    }

    result = malloc(input_length + 1);
    if (result == NULL) {
        return NULL;
    }

    for (source_index = 0; source_index < input_length; ++source_index) {
        unsigned char character = (unsigned char)input[source_index];

        if (character == '_') {
            capitalize_next = 1;
            continue;
        }

        if (capitalize_next) {
            character = (unsigned char)toupper(character);
            capitalize_next = 0;
        }

        result[destination_index++] = (char)character;
    }

    result[destination_index] = '\0';
    return result;
}

int main(int argc, char *argv[const])
{
    size_t input_length = 0;
    char *camel_case;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <snake_case_string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    while (argv[1][input_length] != '\0') {
        if (input_length == SIZE_MAX - 1) {
            fputs("Input string is too long.\n", stderr);
            return EXIT_FAILURE;
        }
        ++input_length;
    }

    camel_case = snake_to_camel(argv[1], input_length);
    if (camel_case == NULL) {
        fputs("Failed to convert string.\n", stderr);
        return EXIT_FAILURE;
    }

    if (puts(camel_case) == EOF) {
        free(camel_case);
        return EXIT_FAILURE;
    }

    free(camel_case);
    return EXIT_SUCCESS;
}