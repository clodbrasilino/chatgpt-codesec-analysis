#include <ctype.h>
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

char *insert_spaces_before_capitals(const char *input)
{
    size_t input_length = 0;
    size_t space_count = 0;
    size_t output_length;
    size_t output_position = 0;
    char *output;

    if (input == NULL) {
        errno = EINVAL;
        return NULL;
    }

    while (input[input_length] != '\0') {
        unsigned char current = (unsigned char)input[input_length];

        if (input_length > 0U) {
            unsigned char previous = (unsigned char)input[input_length - 1U];

            if (isupper(current) && (islower(previous) || isdigit(previous))) {
                if (space_count == SIZE_MAX) {
                    errno = EOVERFLOW;
                    return NULL;
                }
                ++space_count;
            }
        }

        ++input_length;
    }

    if (input_length == SIZE_MAX ||
        space_count > SIZE_MAX - input_length - 1U) {
        errno = EOVERFLOW;
        return NULL;
    }

    output_length = input_length + space_count;
    output = malloc(output_length + 1U);
    if (output == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < input_length; ++i) {
        unsigned char current = (unsigned char)input[i];

        if (i > 0U) {
            unsigned char previous = (unsigned char)input[i - 1U];

            if (isupper(current) && (islower(previous) || isdigit(previous))) {
                output[output_position++] = ' ';
            }
        }

        output[output_position++] = input[i];
    }

    output[output_position] = '\0';
    return output;
}

int main(int argc, char *argv[])
{
    const char *program_name;
    char *result;

    program_name = argc > 0 && argv[0] != NULL ? argv[0] : "program";

    if (argc != 2) {
        fprintf(stderr, "Usage: %s \"string\"\n", program_name);
        return EXIT_FAILURE;
    }

    result = insert_spaces_before_capitals(argv[1]);
    if (result == NULL) {
        perror("Unable to transform string");
        return EXIT_FAILURE;
    }

    if (printf("%s\n", result) < 0) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}