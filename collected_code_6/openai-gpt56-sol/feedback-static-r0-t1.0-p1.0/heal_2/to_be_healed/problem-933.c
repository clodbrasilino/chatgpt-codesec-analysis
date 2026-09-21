#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *camel_to_snake(const char *input)
{
    char *output;
    size_t input_length;
    size_t uppercase_count = 0;
    size_t output_length;
    size_t i;
    size_t j = 0;

    if (input == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    input_length = strlen(input);

    for (i = 1; i < input_length; ++i) {
        unsigned char previous = (unsigned char)input[i - 1];
        unsigned char current = (unsigned char)input[i];

        if (((previous >= (unsigned char)'a' &&
              previous <= (unsigned char)'z') ||
             (previous >= (unsigned char)'0' &&
              previous <= (unsigned char)'9')) &&
            current >= (unsigned char)'A' &&
            current <= (unsigned char)'Z') {
            if (uppercase_count == SIZE_MAX) {
                return NULL;
            }
            ++uppercase_count;
        }
    }

    if (input_length > SIZE_MAX - uppercase_count - 1U) {
        return NULL;
    }

    output_length = input_length + uppercase_count;
    output = malloc(output_length + 1U);
    if (output == NULL) {
        return NULL;
    }

    for (i = 0; i < input_length; ++i) {
        unsigned char current = (unsigned char)input[i];

        if (i > 0U) {
            unsigned char previous = (unsigned char)input[i - 1U];

            if (((previous >= (unsigned char)'a' &&
                  previous <= (unsigned char)'z') ||
                 (previous >= (unsigned char)'0' &&
                  previous <= (unsigned char)'9')) &&
                current >= (unsigned char)'A' &&
                current <= (unsigned char)'Z') {
                output[j++] = '_';
            }
        }

        output[j++] = input[i];
    }

    output[j] = '\0';
    return output;
}

int main(int argc, char *argv[])
{
    char *result;

    if (argc != 2) {
        const char *program = argc > 0 && argv[0] != NULL ? argv[0] : "program";
        fprintf(stderr, "Usage: %s <camelCaseString>\n", program);
        return EXIT_FAILURE;
    }

    result = camel_to_snake(argv[1]);
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