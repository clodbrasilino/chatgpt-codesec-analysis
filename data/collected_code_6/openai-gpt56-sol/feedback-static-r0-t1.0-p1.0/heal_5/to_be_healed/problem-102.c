#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *snake_to_camel(const char *input)
{
    size_t length;
    size_t read_index;
    size_t write_index = 0;
    int capitalize = 0;
    char *output;

    if (input == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
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

int main(int argc, char *argv[])
{
    const char *program_name;
    char *result;

    program_name = (argc > 0 && argv[0] != NULL) ? argv[0] : "program";

    if (argc != 2 || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s snake_case_string\n", program_name);
        return EXIT_FAILURE;
    }

    result = snake_to_camel(argv[1]);
    if (result == NULL) {
        fputs("Failed to convert string\n", stderr);
        return EXIT_FAILURE;
    }

    if (puts(result) == EOF) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}