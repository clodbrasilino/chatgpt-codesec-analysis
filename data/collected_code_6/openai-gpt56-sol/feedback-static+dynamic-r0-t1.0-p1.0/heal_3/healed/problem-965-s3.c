#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

char *camel_to_snake(const char *input, size_t input_length)
{
    size_t uppercase_count = 0;
    size_t output_length;
    size_t i;
    size_t j = 0;
    char *output;

    if (input == NULL) {
        return NULL;
    }

    for (i = 1; i < input_length; ++i) {
        if (isupper((unsigned char)input[i])) {
            if (uppercase_count == SIZE_MAX) {
                return NULL;
            }
            ++uppercase_count;
        }
    }

    if (uppercase_count > SIZE_MAX - input_length - 1) {
        return NULL;
    }

    output_length = input_length + uppercase_count;
    output = malloc(output_length + 1);

    if (output == NULL) {
        return NULL;
    }

    for (i = 0; i < input_length; ++i) {
        unsigned char current = (unsigned char)input[i];

        if (i > 0 && isupper(current)) {
            output[j++] = '_';
        }

        output[j++] = (char)tolower(current);
    }

    output[j] = '\0';
    return output;
}

int main(int argc, char *argv[])
{
    const char *input;
    size_t input_length = 0;
    char *result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <camelCaseString>\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    input = argv[1];

    while (input[input_length] != '\0') {
        if (input_length == SIZE_MAX) {
            fputs("Input string is too long.\n", stderr);
            return EXIT_FAILURE;
        }
        ++input_length;
    }

    result = camel_to_snake(input, input_length);

    if (result == NULL) {
        fputs("Failed to convert the input string.\n", stderr);
        return EXIT_FAILURE;
    }

    if (puts(result) == EOF) {
        free(result);
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}