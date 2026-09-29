#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int append_character(char **buffer, size_t *length, size_t *capacity,
                            char character)
{
    size_t required_capacity;

    if (buffer == NULL || *buffer == NULL ||
        length == NULL || capacity == NULL ||
        *length > SIZE_MAX - 2U) {
        return 0;
    }

    required_capacity = *length + 2U;

    if (required_capacity > *capacity) {
        size_t new_capacity = *capacity;
        char *new_buffer;

        if (new_capacity == 0U) {
            new_capacity = 16U;
        }

        while (new_capacity < required_capacity) {
            if (new_capacity > SIZE_MAX / 2U) {
                new_capacity = required_capacity;
                break;
            }

            new_capacity *= 2U;
        }

        new_buffer = realloc(*buffer, new_capacity);
        if (new_buffer == NULL) {
            return 0;
        }

        *buffer = new_buffer;
        *capacity = new_capacity;
    }

    (*buffer)[*length] = character;
    ++(*length);
    (*buffer)[*length] = '\0';

    return 1;
}

static char *camel_to_snake(const char *input)
{
    size_t input_index = 0U;
    size_t output_length = 0U;
    size_t output_capacity = 16U;
    char *output;

    if (input == NULL) {
        return NULL;
    }

    output = malloc(output_capacity);
    if (output == NULL) {
        return NULL;
    }

    output[0] = '\0';

    while (input[input_index] != '\0') {
        unsigned char current = (unsigned char)input[input_index];

        if (isupper(current)) {
            int follows_lower_or_digit =
                input_index > 0U &&
                (islower((unsigned char)input[input_index - 1U]) ||
                 isdigit((unsigned char)input[input_index - 1U]));

            int starts_word_before_lower =
                input[input_index + 1U] != '\0' &&
                islower((unsigned char)input[input_index + 1U]);

            if ((follows_lower_or_digit || starts_word_before_lower) &&
                output_length > 0U &&
                output[output_length - 1U] != '_') {
                if (!append_character(&output, &output_length,
                                      &output_capacity, '_')) {
                    free(output);
                    return NULL;
                }
            }

            if (!append_character(&output, &output_length, &output_capacity,
                                  (char)tolower(current))) {
                free(output);
                return NULL;
            }
        } else {
            if (!append_character(&output, &output_length, &output_capacity,
                                  (char)current)) {
                free(output);
                return NULL;
            }
        }

        ++input_index;
    }

    return output;
}

int main(int argc, char **argv)
{
    char *snake_case;

    if (argc != 2) {
        fputs("Usage: program <camelCaseString>\n", stderr);
        return EXIT_FAILURE;
    }

    snake_case = camel_to_snake(argv[1]);
    if (snake_case == NULL) {
        fputs("Failed to convert the input string.\n", stderr);
        return EXIT_FAILURE;
    }

    if (fputs(snake_case, stdout) == EOF ||
        fputc('\n', stdout) == EOF) {
        free(snake_case);
        return EXIT_FAILURE;
    }

    free(snake_case);
    return EXIT_SUCCESS;
}