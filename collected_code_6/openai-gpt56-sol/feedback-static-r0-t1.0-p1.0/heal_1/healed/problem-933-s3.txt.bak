#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *camel_to_snake(const char *input)
{
    size_t input_length;
    size_t output_length;
    char *output;
    size_t source;
    size_t destination;

    if (input == NULL) {
        return NULL;
    }

    input_length = strlen(input);
    output_length = input_length;

    for (size_t i = 1; i < input_length; ++i) {
        unsigned char previous = (unsigned char)input[i - 1];
        unsigned char current = (unsigned char)input[i];

        if ((islower(previous) || isdigit(previous)) && isupper(current)) {
            if (output_length == SIZE_MAX) {
                return NULL;
            }
            ++output_length;
        }
    }

    if (output_length == SIZE_MAX) {
        return NULL;
    }

    output = malloc(output_length + 1);
    if (output == NULL) {
        return NULL;
    }

    destination = 0;

    for (source = 0; source < input_length; ++source) {
        unsigned char current = (unsigned char)input[source];

        if (source > 0) {
            unsigned char previous = (unsigned char)input[source - 1];

            if ((islower(previous) || isdigit(previous)) && isupper(current)) {
                output[destination++] = '_';
            }
        }

        output[destination++] = (char)tolower(current);
    }

    output[destination] = '\0';
    return output;
}

int main(int argc, char *const argv[])
{
    char *result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <camelCaseString>\n", argv[0]);
        return EXIT_FAILURE;
    }

    result = camel_to_snake(argv[1]);
    if (result == NULL) {
        fprintf(stderr, "Conversion failed\n");
        return EXIT_FAILURE;
    }

    if (printf("%s\n", result) < 0) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}