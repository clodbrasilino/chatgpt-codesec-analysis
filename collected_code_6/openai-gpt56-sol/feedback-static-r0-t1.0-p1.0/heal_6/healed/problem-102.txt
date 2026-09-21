#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *snake_to_camel(const char *input, size_t input_size)
{
    const char *terminator;
    size_t length;
    size_t read_index;
    size_t write_index = 0;
    int capitalize = 0;
    char *output;

    if (input == NULL || input_size == 0) {
        return NULL;
    }

    terminator = memchr(input, '\0', input_size);
    if (terminator == NULL) {
        return NULL;
    }

    length = (size_t)(terminator - input);
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
    const char *program_name;
    const char *terminator;
    size_t input_size;
    char *result;

    program_name = (argc > 0 && argv[0] != NULL) ? argv[0] : "program";

    if (argc != 2 || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s snake_case_string\n", program_name);
        return EXIT_FAILURE;
    }

    terminator = memchr(argv[1], '\0', SIZE_MAX);
    if (terminator == NULL) {
        fputs("Invalid input string\n", stderr);
        return EXIT_FAILURE;
    }

    input_size = (size_t)(terminator - argv[1]) + 1;
    result = snake_to_camel(argv[1], input_size);
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