#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *camel_to_snake(const char *input, size_t input_length)
{
    size_t output_length = 0;
    size_t i;
    size_t j = 0;
    char *output;

    if (input == NULL) {
        return NULL;
    }

    for (i = 0; i < input_length; ++i) {
        unsigned char current = (unsigned char)input[i];

        if (current == '\0') {
            input_length = i;
            break;
        }

        if (isupper(current)) {
            int previous_is_lower_or_digit =
                i > 0 &&
                (islower((unsigned char)input[i - 1]) ||
                 isdigit((unsigned char)input[i - 1]));
            int next_is_lower =
                i + 1 < input_length &&
                input[i + 1] != '\0' &&
                islower((unsigned char)input[i + 1]);

            if ((previous_is_lower_or_digit || next_is_lower) &&
                output_length > 0) {
                if (output_length == SIZE_MAX) {
                    return NULL;
                }
                ++output_length;
            }
        }

        if (output_length == SIZE_MAX) {
            return NULL;
        }
        ++output_length;
    }

    if (output_length == SIZE_MAX) {
        return NULL;
    }

    output = malloc(output_length + 1);
    if (output == NULL) {
        return NULL;
    }

    for (i = 0; i < input_length; ++i) {
        unsigned char current = (unsigned char)input[i];

        if (isupper(current)) {
            int previous_is_lower_or_digit =
                i > 0 &&
                (islower((unsigned char)input[i - 1]) ||
                 isdigit((unsigned char)input[i - 1]));
            int next_is_lower =
                i + 1 < input_length &&
                islower((unsigned char)input[i + 1]);

            if ((previous_is_lower_or_digit || next_is_lower) && j > 0) {
                output[j++] = '_';
            }

            output[j++] = (char)tolower(current);
        } else {
            output[j++] = (char)current;
        }
    }

    output[j] = '\0';
    return output;
}

int main(int argc, char *argv[])
{
    const char *input;
    char *result;
    size_t input_length;

    if (argc != 2) {
        const char *program_name =
            argc > 0 && argv != NULL && argv[0] != NULL ? argv[0] : "program";

        fprintf(stderr, "Usage: %s <camelCaseString>\n", program_name);
        return EXIT_FAILURE;
    }

    input = argv[1];
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    input_length = strlen(input);

    result = camel_to_snake(input, input_length);
    if (result == NULL) {
        fprintf(stderr, "Failed to convert the input string.\n");
        return EXIT_FAILURE;
    }

    if (printf("%s\n", result) < 0) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}