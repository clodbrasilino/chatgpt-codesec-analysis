#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *camel_to_snake(const char *input)
{
    size_t input_length;
    size_t capacity;
    size_t output_length = 0;
    char *output;

    if (input == NULL) {
        return NULL;
    }

    input_length = strlen(input);
    if (input_length > (SIZE_MAX - 1U) / 2U) {
        return NULL;
    }

    capacity = input_length * 2U + 1U;
    output = malloc(capacity);
    if (output == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < input_length; ++i) {
        unsigned char current = (unsigned char)input[i];
        int add_underscore = 0;

        if (i > 0U && isupper(current)) {
            unsigned char previous = (unsigned char)input[i - 1U];
            int previous_is_lower_or_digit = islower(previous) || isdigit(previous);
            int next_is_lower = i + 1U < input_length &&
                                islower((unsigned char)input[i + 1U]);

            add_underscore = previous_is_lower_or_digit ||
                             (isupper(previous) && next_is_lower);
        }

        if (add_underscore && output_length > 0U &&
            output[output_length - 1U] != '_') {
            output[output_length++] = '_';
        }

        output[output_length++] = (char)tolower(current);
    }

    output[output_length] = '\0';
    return output;
}

int main(int argc, char *argv[])
{
    char *result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <camelCaseString>\n", argv[0]);
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