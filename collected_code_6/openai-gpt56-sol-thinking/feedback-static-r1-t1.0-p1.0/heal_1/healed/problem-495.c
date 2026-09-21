#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    REMOVE_SUCCESS = 0,
    REMOVE_INVALID_ARGUMENT,
    REMOVE_MEMORY_FAILURE,
    REMOVE_REGEX_FAILURE,
    REMOVE_RANGE_FAILURE
} RemoveResult;

RemoveResult remove_lowercase_substrings(const char *input,
                                         size_t input_length,
                                         char **output)
{
    char *buffer;
    size_t input_offset;
    size_t output_offset = 0;

    if (output == NULL) {
        return REMOVE_INVALID_ARGUMENT;
    }

    *output = NULL;

    if (input == NULL) {
        return REMOVE_INVALID_ARGUMENT;
    }

    if (input_length == SIZE_MAX) {
        return REMOVE_RANGE_FAILURE;
    }

    buffer = malloc(input_length + 1U);
    if (buffer == NULL) {
        return REMOVE_MEMORY_FAILURE;
    }

    for (input_offset = 0; input_offset < input_length; ++input_offset) {
        unsigned char character = (unsigned char)input[input_offset];

        if (!islower(character)) {
            buffer[output_offset++] = (char)character;
        }
    }

    buffer[output_offset] = '\0';
    *output = buffer;

    return REMOVE_SUCCESS;
}

int main(int argc, char *argv[])
{
    const char *program_name;
    size_t input_length = 0;
    char *result = NULL;
    RemoveResult status;

    program_name = argc > 0 && argv[0] != NULL ? argv[0] : "program";

    if (argc != 2 || argv[1] == NULL) {
        if (fprintf(stderr, "Usage: %s <string>\n", program_name) < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    while (argv[1][input_length] != '\0') {
        ++input_length;
    }

    status = remove_lowercase_substrings(argv[1], input_length, &result);
    if (status != REMOVE_SUCCESS) {
        if (fprintf(stderr, "Failed to process the input string.\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("%s\n", result) < 0) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}