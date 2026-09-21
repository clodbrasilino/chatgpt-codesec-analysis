#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    CONVERT_SUCCESS,
    CONVERT_INVALID_ARGUMENT,
    CONVERT_NO_MEMORY,
    CONVERT_REGEX_ERROR
} ConvertStatus;

static int is_ascii_alphanumeric(unsigned char character)
{
    return (character >= 'A' && character <= 'Z') ||
           (character >= 'a' && character <= 'z') ||
           (character >= '0' && character <= '9');
}

static char to_ascii_upper(unsigned char character)
{
    if (character >= 'a' && character <= 'z') {
        character = (unsigned char)(character - ('a' - 'A'));
    }

    return (char)character;
}

static size_t string_length(const char *string)
{
    size_t length = 0;

    while (string[length] != '\0') {
        ++length;
    }

    return length;
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

    if (input_length == SIZE_MAX) {
        return CONVERT_NO_MEMORY;
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

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char *argv[const])
{
    const char *program_name;
    size_t input_length;
    char *camel_case = NULL;
    ConvertStatus status;
    int output_status;

    program_name = argc > 0 && argv[0] != NULL ? argv[0] : "program";

    if (argc != 2) {
        fprintf(stderr, "Usage: %s snake_case_string\n", program_name);
        return EXIT_FAILURE;
    }

    input_length = string_length(argv[1]);
    status = snake_to_camel(argv[1], input_length, &camel_case);

    if (status != CONVERT_SUCCESS) {
        fputs("Failed to convert the input string.\n", stderr);
        return EXIT_FAILURE;
    }

    output_status = puts(camel_case);
    free(camel_case);

    return output_status == EOF ? EXIT_FAILURE : EXIT_SUCCESS;
}