#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

        if (character == (unsigned char)'_') {
            capitalize_next = 1;
            continue;
        }

        if (capitalize_next != 0) {
            character = (unsigned char)toupper((int)character);
            capitalize_next = 0;
        }

        result[destination_index] = (char)character;
        ++destination_index;
    }

    result[destination_index] = '\0';
    return result;
}

int main(int argc, char **argv)
{
    const char *program_name;
    size_t input_length;
    char *camel_case;

    program_name = "program";
    if (argc > 0 && argv != NULL && argv[0] != NULL) {
        program_name = argv[0];
    }

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s <snake_case_string>\n", program_name);
        return EXIT_FAILURE;
    }

    input_length = strlen(argv[1]);
    if (input_length == SIZE_MAX) {
        fputs("Input string is too long.\n", stderr);
        return EXIT_FAILURE;
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