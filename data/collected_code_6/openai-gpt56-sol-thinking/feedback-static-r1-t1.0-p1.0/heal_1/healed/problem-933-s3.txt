#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    CAMEL_OK = 0,
    CAMEL_INVALID_ARGUMENT,
    CAMEL_OUT_OF_MEMORY,
    CAMEL_OVERFLOW
} CamelStatus;

static int is_ascii_upper(char character)
{
    return character >= 'A' && character <= 'Z';
}

static int is_ascii_lower(char character)
{
    return character >= 'a' && character <= 'z';
}

static int is_ascii_digit(char character)
{
    return character >= '0' && character <= '9';
}

static int has_boundary_before(
    const char *input,
    size_t input_length,
    size_t index)
{
    char previous;
    char current;

    if (index == 0 || index >= input_length) {
        return 0;
    }

    previous = input[index - 1];
    current = input[index];

    if (!is_ascii_upper(current)) {
        return 0;
    }

    if (is_ascii_lower(previous) || is_ascii_digit(previous)) {
        return 1;
    }

    return is_ascii_upper(previous) &&
           index + 1 < input_length &&
           is_ascii_lower(input[index + 1]);
}

CamelStatus camel_to_snake(
    const char *input,
    size_t input_length,
    char **output)
{
    size_t index;
    size_t boundary_count;
    size_t output_length;
    size_t destination;
    char *result;

    if (output == NULL) {
        return CAMEL_INVALID_ARGUMENT;
    }

    *output = NULL;

    if (input == NULL) {
        return CAMEL_INVALID_ARGUMENT;
    }

    if (input_length == SIZE_MAX) {
        return CAMEL_OVERFLOW;
    }

    boundary_count = 0;

    for (index = 1; index < input_length; ++index) {
        if (has_boundary_before(input, input_length, index)) {
            if (boundary_count == SIZE_MAX) {
                return CAMEL_OVERFLOW;
            }

            ++boundary_count;
        }
    }

    if (boundary_count > SIZE_MAX - input_length - 1) {
        return CAMEL_OVERFLOW;
    }

    output_length = input_length + boundary_count;
    result = malloc(output_length + 1);

    if (result == NULL) {
        return CAMEL_OUT_OF_MEMORY;
    }

    destination = 0;

    for (index = 0; index < input_length; ++index) {
        char character = input[index];

        if (has_boundary_before(input, input_length, index)) {
            result[destination++] = '_';
        }

        if (is_ascii_upper(character)) {
            character = (char)(character - 'A' + 'a');
        }

        result[destination++] = character;
    }

    if (destination != output_length) {
        free(result);
        return CAMEL_OVERFLOW;
    }

    result[destination] = '\0';
    *output = result;

    return CAMEL_OK;
}

static const char *camel_status_message(CamelStatus status)
{
    switch (status) {
        case CAMEL_OK:
            return "success";
        case CAMEL_INVALID_ARGUMENT:
            return "invalid argument";
        case CAMEL_OUT_OF_MEMORY:
            return "out of memory";
        case CAMEL_OVERFLOW:
            return "size overflow";
        default:
            return "unknown error";
    }
}

int main(int argc, char *argv[])
{
    const char *input;
    size_t input_length;
    char *snake_case;
    CamelStatus status;
    int print_result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <camelCaseString>\n", argv[0]);
        return EXIT_FAILURE;
    }

    input = argv[1];
    input_length = 0;

    while (input[input_length] != '\0') {
        ++input_length;
    }

    status = camel_to_snake(input, input_length, &snake_case);

    if (status != CAMEL_OK) {
        fprintf(
            stderr,
            "Conversion failed: %s\n",
            camel_status_message(status));
        return EXIT_FAILURE;
    }

    print_result = printf("%s\n", snake_case);
    free(snake_case);

    if (print_result < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}