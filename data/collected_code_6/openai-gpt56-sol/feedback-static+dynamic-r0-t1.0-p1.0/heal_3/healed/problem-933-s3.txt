#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

char *camel_to_snake(const char *input, size_t input_size)
{
    size_t length = 0;
    size_t uppercase_boundaries = 0;
    size_t output_length;
    size_t j = 0;
    char *output;

    if (input == NULL || input_size == 0) {
        return NULL;
    }

    while (length < input_size && input[length] != '\0') {
        ++length;
    }

    if (length == input_size) {
        return NULL;
    }

    for (size_t i = 1; i < length; ++i) {
        unsigned char previous = (unsigned char)input[i - 1];
        unsigned char current = (unsigned char)input[i];

        if ((islower(previous) || isdigit(previous)) && isupper(current)) {
            ++uppercase_boundaries;
        }
    }

    if (uppercase_boundaries > SIZE_MAX - length - 1) {
        return NULL;
    }

    output_length = length + uppercase_boundaries;
    output = malloc(output_length + 1);
    if (output == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < length; ++i) {
        unsigned char current = (unsigned char)input[i];

        if (i > 0) {
            unsigned char previous = (unsigned char)input[i - 1];

            if ((islower(previous) || isdigit(previous)) && isupper(current)) {
                output[j++] = '_';
            }
        }

        output[j++] = (char)tolower(current);
    }

    output[j] = '\0';
    return output;
}

int main(int argc, char *argv[])
{
    char *result;
    size_t input_size = 0;

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        const char *program =
            argc > 0 && argv != NULL && argv[0] != NULL ? argv[0] : "program";

        fprintf(stderr, "Usage: %s <camelCaseString>\n", program);
        return EXIT_FAILURE;
    }

    while (argv[1][input_size] != '\0') {
        if (input_size == SIZE_MAX - 1) {
            fputs("Input is too large\n", stderr);
            return EXIT_FAILURE;
        }
        ++input_size;
    }

    ++input_size;
    result = camel_to_snake(argv[1], input_size);

    if (result == NULL) {
        fputs("Conversion failed\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%s\n", result) < 0) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}