#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int needs_separator(const char *input, size_t input_length, size_t index)
{
    unsigned char previous;
    unsigned char next;
    int follows_lower_or_digit;
    int starts_word_before_lower;

    if (index == 0U || input[index - 1U] == '_') {
        return 0;
    }

    previous = (unsigned char)input[index - 1U];

    follows_lower_or_digit = islower(previous) || isdigit(previous);

    starts_word_before_lower = 0;
    if (index < input_length - 1U) {
        next = (unsigned char)input[index + 1U];
        starts_word_before_lower = islower(next);
    }

    return follows_lower_or_digit || starts_word_before_lower;
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
            output[output_index++] = (char)current;
        }
    }

    output[output_index] = '\0';
    return output;
}

int main(int argc, char **argv)
{
    const char *program_name;
    size_t input_length;
    char *snake_case;

    program_name =
        argc > 0 && argv != NULL && argv[0] != NULL
            ? argv[0]
            : "camel_to_snake";

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        if (fprintf(stderr, "Usage: %s <camelCaseString>\n", program_name) < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    input_length = strlen(argv[1]);
    snake_case = camel_to_snake(argv[1], input_length);

    if (snake_case == NULL) {
        if (fputs("Failed to convert the input string.\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("%s\n", snake_case) < 0) {
        free(snake_case);
        return EXIT_FAILURE;
    }

    free(snake_case);
    return EXIT_SUCCESS;
}