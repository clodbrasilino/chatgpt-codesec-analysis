#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    CAMEL_OK = 0,
    CAMEL_INVALID_ARGUMENT,
    CAMEL_OUT_OF_MEMORY,
    CAMEL_OVERFLOW
} CamelStatus;

static int is_ascii_upper(unsigned char character)
{
    return character >= (unsigned char)'A' &&
           character <= (unsigned char)'Z';
}

static int is_ascii_lower(unsigned char character)
{
    return character >= (unsigned char)'a' &&
           character <= (unsigned char)'z';
}

static int is_ascii_digit(unsigned char character)
{
    return character >= (unsigned char)'0' &&
           character <= (unsigned char)'9';
}

static unsigned char to_ascii_lower(unsigned char character)
{
    if (is_ascii_upper(character)) {
        return (unsigned char)(character - (unsigned char)'A' +
                               (unsigned char)'a');
    }

    return character;
}

static int needs_boundary(const char *input, size_t length, size_t index)
{
    unsigned char previous;
    unsigned char current;
    unsigned char next;

    if (index == 0 || index >= length) {
        return 0;
    }

    current = (unsigned char)input[index];

    if (!is_ascii_upper(current)) {
        return 0;
    }

    previous = (unsigned char)input[index - 1];

    if (is_ascii_lower(previous) || is_ascii_digit(previous)) {
        return 1;
    }

    if (!is_ascii_upper(previous) || index + 1 >= length) {
        return 0;
    }

    next = (unsigned char)input[index + 1];
    return is_ascii_lower(next);
}

CamelStatus camel_to_snake(const char *input, size_t input_length, char **output)
{
    size_t boundary_count;
    size_t output_length;
    size_t destination;
    size_t index;
    char *result;

    if (input == NULL || output == NULL) {
        return CAMEL_INVALID_ARGUMENT;
    }

    *output = NULL;
    boundary_count = 0;

    for (index = 0; index < input_length; ++index) {
        if (needs_boundary(input, input_length, index)) {
            if (boundary_count == SIZE_MAX) {
                return CAMEL_OVERFLOW;
            }

            ++boundary_count;
        }
    }

    if (boundary_count > SIZE_MAX - input_length) {
        return CAMEL_OVERFLOW;
    }

    output_length = input_length + boundary_count;

    if (output_length == SIZE_MAX) {
        return CAMEL_OVERFLOW;
    }

    result = malloc(output_length + 1);

    if (result == NULL) {
        return CAMEL_OUT_OF_MEMORY;
    }

    destination = 0;

    for (index = 0; index < input_length; ++index) {
        if (needs_boundary(input, input_length, index)) {
            if (destination >= output_length) {
                free(result);
                return CAMEL_OVERFLOW;
            }

            result[destination++] = '_';
        }

        if (destination >= output_length) {
            free(result);
            return CAMEL_OVERFLOW;
        }

        result[destination++] =
            (char)to_ascii_lower((unsigned char)input[index]);
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

static CamelStatus argument_length(const char *argument, size_t *length)
{
    const char *cursor;
    size_t result;

    if (argument == NULL || length == NULL) {
        return CAMEL_INVALID_ARGUMENT;
    }

    cursor = argument;
    result = 0;

    while (*cursor != '\0') {
        if (result == SIZE_MAX) {
            return CAMEL_OVERFLOW;
        }

        ++cursor;
        ++result;
    }

    *length = result;
    return CAMEL_OK;
}

int main(int argc, char *const argv[])
{
    char *snake_case;
    CamelStatus status;
    size_t input_length;
    int print_result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <camelCaseString>\n",
                argc > 0 && argv[0] != NULL
                    ? argv[0]
                    : "camel_to_snake");
        return EXIT_FAILURE;
    }

    status = argument_length(argv[1], &input_length);

    if (status != CAMEL_OK) {
        fprintf(stderr, "Conversion failed: %s\n",
                camel_status_message(status));
        return EXIT_FAILURE;
    }

    status = camel_to_snake(argv[1], input_length, &snake_case);

    if (status != CAMEL_OK) {
        fprintf(stderr, "Conversion failed: %s\n",
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