#include <ctype.h>
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *insert_spaces_before_capitals(const char *input)
{
    size_t input_length;
    size_t spaces = 0;
    size_t output_length;
    size_t output_position = 0;
    char *output;

    if (input == NULL) {
        errno = EINVAL;
        return NULL;
    }

    input_length = strlen(input);

    for (size_t i = 1; i < input_length; ++i) {
        unsigned char previous = (unsigned char)input[i - 1];
        unsigned char current = (unsigned char)input[i];

        if ((islower(previous) || isdigit(previous)) && isupper(current)) {
            ++spaces;
        }
    }

    if (input_length == SIZE_MAX ||
        spaces > SIZE_MAX - input_length - 1U) {
        errno = EOVERFLOW;
        return NULL;
    }

    output_length = input_length + spaces;
    output = malloc(output_length + 1U);
    if (output == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < input_length; ++i) {
        unsigned char current = (unsigned char)input[i];

        if (i > 0) {
            unsigned char previous = (unsigned char)input[i - 1];

            if ((islower(previous) || isdigit(previous)) && isupper(current)) {
                output[output_position++] = ' ';
            }
        }

        output[output_position++] = input[i];
    }

    output[output_position] = '\0';
    return output;
}

int main(int argc, char * const argv[])
{
    const char *program_name;
    char *result;

    program_name = argc > 0 && argv[0] != NULL ? argv[0] : "program";

    if (argc != 2 || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s \"string\"\n", program_name);
        return EXIT_FAILURE;
    }

    result = insert_spaces_before_capitals(argv[1]);
    if (result == NULL) {
        perror("Unable to transform string");
        return EXIT_FAILURE;
    }

    if (puts(result) == EOF) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}