#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *snake_to_camel(const char *input)
{
    size_t input_length;
    size_t source_index;
    size_t destination_index = 0;
    int capitalize_next = 1;
    char *result;

    if (input == NULL) {
        return NULL;
    }

    input_length = strlen(input);
    if (input_length == SIZE_MAX) {
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

        if (capitalize_next) {
            character = (unsigned char)toupper(character);
            capitalize_next = 0;
        }

        result[destination_index++] = (char)character;
    }

    result[destination_index] = '\0';
    return result;
}

int main(int argc, char **argv)
{
    const char *program_name;
    char *camel_case;

    program_name = argc > 0 && argv != NULL && argv[0] != NULL
        ? argv[0]
        : "program";

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s <snake_case_string>\n", program_name);
        return EXIT_FAILURE;
    }

    camel_case = snake_to_camel(argv[1]);
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