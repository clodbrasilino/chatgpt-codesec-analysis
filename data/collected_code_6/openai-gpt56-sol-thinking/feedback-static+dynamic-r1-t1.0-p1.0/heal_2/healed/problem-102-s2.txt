#include <ctype.h>
#include <stddef.h>
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
        unsigned char current = (unsigned char)input[read_index];

        if (current == '_') {
            capitalize_next = 1;
            continue;
        }

        output[write_index++] = capitalize_next
            ? (char)toupper((int)current)
            : (char)current;
        capitalize_next = 0;
    }

    output[write_index] = '\0';
    return output;
}

int main(int argc, char **const argv)
{
    char *converted;
    size_t input_length = 0;
    int status = EXIT_SUCCESS;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s snake_case_string\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    while (argv[1][input_length] != '\0') {
        if (input_length == SIZE_MAX - 1) {
            fputs("Input string is too long.\n", stderr);
            return EXIT_FAILURE;
        }
        ++input_length;
    }

    converted = snake_to_camel(argv[1], input_length);
    if (converted == NULL) {
        fputs("Failed to convert the string.\n", stderr);
        return EXIT_FAILURE;
    }

    if (puts(converted) == EOF) {
        fputs("Failed to write the converted string.\n", stderr);
        status = EXIT_FAILURE;
    }

    free(converted);
    return status;
}