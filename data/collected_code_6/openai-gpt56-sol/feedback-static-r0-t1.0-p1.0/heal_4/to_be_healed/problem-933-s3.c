#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *camel_to_snake_n(const char *input, size_t input_size)
{
    size_t length;
    size_t boundaries = 0;
    size_t output_length;
    size_t j = 0;
    char *output;

    if (input == NULL) {
        return NULL;
    }

    for (length = 0; length < input_size; ++length) {
        if (input[length] == '\0') {
            break;
        }
    }

    if (length == input_size) {
        return NULL;
    }

    for (size_t i = 1; i < length; ++i) {
        unsigned char previous = (unsigned char)input[i - 1];
        unsigned char current = (unsigned char)input[i];

        if ((islower(previous) || isdigit(previous)) && isupper(current)) {
            ++boundaries;
        }
    }

    if (length > SIZE_MAX - boundaries ||
        length + boundaries == SIZE_MAX) {
        return NULL;
    }

    output_length = length + boundaries;
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
    const char *program;

    program = (argc > 0 && argv != NULL && argv[0] != NULL)
                  ? argv[0]
                  : "program";

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s <camelCaseString>\n", program);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    result = camel_to_snake_n(argv[1], strlen(argv[1]) + 1);
    if (result == NULL) {
        fputs("Conversion failed\n", stderr);
        return EXIT_FAILURE;
    }

    if (puts(result) == EOF) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}