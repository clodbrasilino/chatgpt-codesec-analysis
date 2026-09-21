#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *camel_to_snake(const char *input, size_t input_length)
{
    size_t input_index;
    size_t output_index = 0;
    size_t output_capacity;
    char *output;

    if (input == NULL || input_length > (SIZE_MAX - 1U) / 2U) {
        return NULL;
    }

    output_capacity = input_length * 2U + 1U;
    output = malloc(output_capacity);
    if (output == NULL) {
        return NULL;
    }

    for (input_index = 0; input_index < input_length; ++input_index) {
        unsigned char current = (unsigned char)input[input_index];

        if (isupper(current)) {
            int follows_lower_or_digit =
                input_index > 0U &&
                (islower((unsigned char)input[input_index - 1U]) ||
                 isdigit((unsigned char)input[input_index - 1U]));

            int starts_word_before_lower =
                input_index > 0U &&
                input_index + 1U < input_length &&
                islower((unsigned char)input[input_index + 1U]);

            if ((follows_lower_or_digit || starts_word_before_lower) &&
                output_index > 0U &&
                output[output_index - 1U] != '_') {
                if (output_index >= output_capacity - 1U) {
                    free(output);
                    return NULL;
                }
                output[output_index++] = '_';
            }

            if (output_index >= output_capacity - 1U) {
                free(output);
                return NULL;
            }

            output[output_index++] = (char)tolower(current);
        } else {
            if (output_index >= output_capacity - 1U) {
                free(output);
                return NULL;
            }

            output[output_index++] = (char)current;
        }
    }

    output[output_index] = '\0';
    return output;
}

int main(int argc, char **argv)
{
    size_t input_length;
    char *snake_case;

    if (argc != 2) {
        if (fputs("Usage: program <camelCaseString>\n", stderr) == EOF) {
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

    if (fputs(snake_case, stdout) == EOF || fputc('\n', stdout) == EOF) {
        free(snake_case);
        return EXIT_FAILURE;
    }

    free(snake_case);
    return EXIT_SUCCESS;
}