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

static unsigned char to_ascii_upper(unsigned char character)
{
    if (character >= (unsigned char)'a' &&
        character <= (unsigned char)'z') {
        return (unsigned char)(character -
                               ((unsigned char)'a' - (unsigned char)'A'));
    }

    return character;
}

ConvertStatus snake_to_camel(const char *input, size_t input_length,
                             char **output)
{
    char *result;
    size_t read_offset = 0;
    size_t write_offset = 0;

    if (input == NULL || output == NULL) {
        return CONVERT_INVALID_ARGUMENT;
    }

    *output = NULL;

    if (input_length == SIZE_MAX) {
        return CONVERT_NO_MEMORY;
    }

    if (memchr(input, '\0', input_length) != NULL) {
        return CONVERT_INVALID_ARGUMENT;
    }

    result = malloc(input_length + 1);
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

        if (read_offset < input_length) {
            character = (unsigned char)input[read_offset];

            if (is_ascii_alphanumeric(character)) {
                result[write_offset++] = (char)to_ascii_upper(character);
                ++read_offset;
            }
        }
    }

    result[write_offset] = '\0';
    *output = result;

    return CONVERT_SUCCESS;
}

int main(int argc, char **argv)
{
    char *camel_case = NULL;
    size_t input_length;
    ConvertStatus status;
    int output_status;

    if (argc != 2) {
        fputs("Usage: snake_to_camel snake_case_string\n", stderr);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    input_length = strlen(argv[1]);

    status = snake_to_camel(argv[1], input_length, &camel_case);
    if (status != CONVERT_SUCCESS) {
        fputs("Failed to convert the input string.\n", stderr);
        return EXIT_FAILURE;
    }

    output_status = puts(camel_case);
    free(camel_case);

    return output_status == EOF ? EXIT_FAILURE : EXIT_SUCCESS;
}