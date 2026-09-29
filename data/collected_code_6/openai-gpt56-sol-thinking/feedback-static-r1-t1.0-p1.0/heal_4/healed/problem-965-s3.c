#include <ctype.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_INPUT_LENGTH ((size_t)1048576U)

static int bounded_string_length(const char *input, size_t maximum,
                                 size_t *length)
{
    size_t index;

    if (input == NULL || length == NULL) {
        return 0;
    }

    for (index = 0U; index <= maximum; ++index) {
        if (input[index] == '\0') {
            *length = index;
            return 1;
        }
    }

    return 0;
}

static int needs_separator(const char *input, size_t input_length, size_t index)
{
    unsigned char previous;
    int follows_lower_or_digit;

    if (index == 0U || index >= input_length || input[index - 1U] == '_') {
        return 0;
    }

    previous = (unsigned char)input[index - 1U];
    follows_lower_or_digit = islower(previous) || isdigit(previous);

    if (index + 1U < input_length) {
        unsigned char next = (unsigned char)input[index + 1U];
        return follows_lower_or_digit || islower(next);
    }

    return follows_lower_or_digit;
}

char *camel_to_snake(const char *input, size_t input_length)
{
    size_t input_index;
    size_t output_length = 0U;
    size_t output_index = 0U;
    char *output;

    if (input == NULL) {
        return NULL;
    }

    for (input_index = 0U; input_index < input_length; ++input_index) {
        unsigned char current = (unsigned char)input[input_index];

        if (isupper(current) &&
            needs_separator(input, input_length, input_index)) {
            if (output_length == SIZE_MAX) {
                return NULL;
            }
            ++output_length;
        }

        if (output_length == SIZE_MAX) {
            return NULL;
        }
        ++output_length;
    }

    if (output_length == SIZE_MAX) {
        return NULL;
    }

    output = malloc(output_length + 1U);
    if (output == NULL) {
        return NULL;
    }

    for (input_index = 0U; input_index < input_length; ++input_index) {
        unsigned char current = (unsigned char)input[input_index];

        if (isupper(current)) {
            if (needs_separator(input, input_length, input_index)) {
                output[output_index++] = '_';
            }

            output[output_index++] = (char)tolower(current);
        } else {
            output[output_index++] = input[input_index];
        }
    }

    output[output_index] = '\0';
    return output;
}

int main(int argc, char *argv[])
{
    const char *program_name;
    size_t input_length;
    char *snake_case;

    program_name = argc > 0 && argv != NULL && argv[0] != NULL
        ? argv[0]
        : "camel_to_snake";

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s <camelCaseString>\n", program_name);
        return EXIT_FAILURE;
    }

    if (!bounded_string_length(argv[1], MAX_INPUT_LENGTH, &input_length)) {
        fputs("Input string is too long.\n", stderr);
        return EXIT_FAILURE;
    }

    snake_case = camel_to_snake(argv[1], input_length);
    if (snake_case == NULL) {
        fputs("Failed to convert the input string.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%s\n", snake_case) < 0) {
        free(snake_case);
        return EXIT_FAILURE;
    }

    free(snake_case);
    return EXIT_SUCCESS;
}