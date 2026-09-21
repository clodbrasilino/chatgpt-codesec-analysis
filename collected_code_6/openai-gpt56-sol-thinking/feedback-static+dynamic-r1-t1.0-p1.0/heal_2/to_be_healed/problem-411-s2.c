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
    return (character >= 'A' && character <= 'Z') ||
           (character >= 'a' && character <= 'z') ||
           (character >= '0' && character <= '9');
}

static unsigned char to_ascii_upper(unsigned char character)
{
    if (character >= 'a' && character <= 'z') {
        return (unsigned char)(character - ('a' - 'A'));
    }

    return character;
}

ConvertStatus snake_to_camel(const char *input, size_t input_length, char **output)
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

        if (character != '_') {
            result[write_offset++] = (char)character;
            ++read_offset;
            continue;
        }

        do {
            ++read_offset;
        } while (read_offset < input_length && input[read_offset] == '_');

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

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char *argv[const])
{
    char *camel_case = NULL;
    size_t input_length = 0;
    ConvertStatus status;
    int output_status;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s snake_case_string\n", argv[0]);
        return EXIT_FAILURE;
    }

    while (argv[1][input_length] != '\0') {
        if (input_length == SIZE_MAX - 1) {
            fputs("Input string is too long.\n", stderr);
            return EXIT_FAILURE;
        }

        ++input_length;
    }

    status = snake_to_camel(argv[1], input_length, &camel_case);
    if (status != CONVERT_SUCCESS) {
        fputs("Failed to convert the input string.\n", stderr);
        return EXIT_FAILURE;
    }

    output_status = printf("%s\n", camel_case);
    free(camel_case);

    return output_status < 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}