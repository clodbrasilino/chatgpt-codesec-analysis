#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *camel_to_snake(const char *input)
{
    if (input == NULL) {
        return NULL;
    }

    const size_t input_length = strlen(input);
    size_t output_length = input_length;

    for (size_t i = 1; i < input_length; ++i) {
        const unsigned char previous = (unsigned char)input[i - 1];
        const unsigned char current = (unsigned char)input[i];

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

    char *output = malloc(output_length + 1);
    if (output == NULL) {
        return NULL;
    }

    size_t destination = 0;

    for (size_t source = 0; source < input_length; ++source) {
        const unsigned char current = (unsigned char)input[source];

        if (source > 0) {
            const unsigned char previous = (unsigned char)input[source - 1];

            if ((islower(previous) || isdigit(previous)) && isupper(current)) {
                output[destination++] = '_';
            }
        }

        output[destination++] = (char)tolower(current);
    }

    output[destination] = '\0';
    return output;
}

int main(int argc, const char *const argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <camelCaseString>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *result = camel_to_snake(argv[1]);
    if (result == NULL) {
        fprintf(stderr, "Conversion failed\n");
        return EXIT_FAILURE;
    }

    const int status = printf("%s\n", result);
    free(result);

    return status < 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}