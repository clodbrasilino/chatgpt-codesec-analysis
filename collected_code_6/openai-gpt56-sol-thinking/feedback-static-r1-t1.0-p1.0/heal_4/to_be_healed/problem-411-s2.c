#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    CONVERT_SUCCESS,
    CONVERT_INVALID_ARGUMENT,
    CONVERT_NO_MEMORY
} ConvertStatus;

static int is_ascii_alphanumeric(unsigned char character)
{
    return (character >= (unsigned char)'A' &&
            character <= (unsigned char)'Z') ||
           (character >= (unsigned char)'a' &&
            character <= (unsigned char)'z') ||
           (character >= (unsigned char)'0' &&
            character <= (unsigned char)'9');
}

static char to_ascii_upper(unsigned char character)
{
    if (character >= (unsigned char)'a' &&
        character <= (unsigned char)'z') {
        character = (unsigned char)(character -
                                    ((unsigned char)'a' -
                                     (unsigned char)'A'));
    }

    return (char)character;
}

ConvertStatus snake_to_camel(const char *input, size_t input_length, char **output)
{
    size_t read_offset = 0;
    size_t write_offset = 0;
    char *result;

    if (output == NULL) {
        return CONVERT_INVALID_ARGUMENT;
    }

    *output = NULL;

    if (input == NULL) {
        return CONVERT_INVALID_ARGUMENT;
    }

    if (input_length > SIZE_MAX - 1U) {
        return CONVERT_NO_MEMORY;
    }

    result = malloc(input_length + 1U);
    if (result == NULL) {
        return CONVERT_NO_MEMORY;
    }

    while (read_offset < input_length) {
        unsigned char character = (unsigned char)input[read_offset];

        if (character != (unsigned char)'_') {
            result[write_offset++] = (char)character;
            ++read_offset;
            continue;
        }

        do {
            ++read_offset;
        } while (read_offset < input_length &&
                 input[read_offset] == '_');

        if (read_offset < input_length &&
            is_ascii_alphanumeric((unsigned char)input[read_offset])) {
            result[write_offset++] =
                to_ascii_upper((unsigned char)input[read_offset]);
            ++read_offset;
        }
    }

    result[write_offset] = '\0';
    *output = result;

    return CONVERT_SUCCESS;
}

int main(int argc, char **argv)
{
    const char *program_name;
    const char *input;
    size_t input_length;
    char *camel_case = NULL;
    ConvertStatus status;
    int output_status;

    program_name = (argc > 0 && argv != NULL && argv[0] != NULL)
                       ? argv[0]
                       : "program";

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s snake_case_string\n", program_name);
        return EXIT_FAILURE;
    }

    input = argv[1];
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    input_length = strlen(input);

    status = snake_to_camel(input, input_length, &camel_case);
    if (status != CONVERT_SUCCESS) {
        fputs("Failed to convert the input string.\n", stderr);
        return EXIT_FAILURE;
    }

    output_status = puts(camel_case);
    free(camel_case);

    return output_status == EOF ? EXIT_FAILURE : EXIT_SUCCESS;
}