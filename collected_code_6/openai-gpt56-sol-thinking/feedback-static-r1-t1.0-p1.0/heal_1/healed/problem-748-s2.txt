#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    SPACE_STATUS_OK = 0,
    SPACE_STATUS_INVALID_ARGUMENT,
    SPACE_STATUS_OVERFLOW,
    SPACE_STATUS_ALLOCATION_FAILURE,
    SPACE_STATUS_REGEX_FAILURE
} SpaceStatus;

SpaceStatus add_spaces_between_words(const char *input,
                                     size_t input_length,
                                     char **result)
{
    char *output;
    size_t capacity;
    size_t output_length = 0;
    size_t i;

    if (input == NULL || result == NULL) {
        return SPACE_STATUS_INVALID_ARGUMENT;
    }

    *result = NULL;

    if (input_length > (SIZE_MAX - 1U) / 2U) {
        return SPACE_STATUS_OVERFLOW;
    }

    for (i = 0; i < input_length; ++i) {
        if (input[i] == '\0') {
            return SPACE_STATUS_INVALID_ARGUMENT;
        }
    }

    capacity = input_length * 2U + 1U;
    output = malloc(capacity);
    if (output == NULL) {
        return SPACE_STATUS_ALLOCATION_FAILURE;
    }

    for (i = 0; i < input_length; ++i) {
        unsigned char current = (unsigned char)input[i];

        if (i > 0U &&
            isupper(current) &&
            !isspace((unsigned char)input[i - 1U])) {
            if (output_length >= capacity - 1U) {
                free(output);
                return SPACE_STATUS_OVERFLOW;
            }

            output[output_length++] = ' ';
        }

        if (output_length >= capacity - 1U) {
            free(output);
            return SPACE_STATUS_OVERFLOW;
        }

        output[output_length++] = (char)current;
    }

    output[output_length] = '\0';
    *result = output;

    return SPACE_STATUS_OK;
}

int main(int argc, char *argv[])
{
    const char *input;
    char *result = NULL;
    size_t input_length = 0;
    SpaceStatus status;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    input = argv[1];

    while (input[input_length] != '\0') {
        if (input_length == SIZE_MAX) {
            fprintf(stderr, "Input is too large\n");
            return EXIT_FAILURE;
        }

        ++input_length;
    }

    status = add_spaces_between_words(input, input_length, &result);
    if (status != SPACE_STATUS_OK) {
        fprintf(stderr, "Failed to process the string\n");
        return EXIT_FAILURE;
    }

    if (fputs(result, stdout) == EOF || fputc('\n', stdout) == EOF) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}