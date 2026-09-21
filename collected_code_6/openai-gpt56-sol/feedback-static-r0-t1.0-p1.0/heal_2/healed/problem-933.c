#include <stdio.h>
#include <stdlib.h>

static int is_lower_or_digit(unsigned char c)
{
    return (c >= (unsigned char)'a' && c <= (unsigned char)'z') ||
           (c >= (unsigned char)'0' && c <= (unsigned char)'9');
}

static int is_upper(unsigned char c)
{
    return c >= (unsigned char)'A' && c <= (unsigned char)'Z';
}

static char *camel_to_snake(const char *input, size_t input_length)
{
    char *output;
    size_t uppercase_count = 0;
    size_t output_length;
    size_t i;
    size_t j = 0;

    if (input == NULL) {
        return NULL;
    }

    for (i = 1; i < input_length; ++i) {
        unsigned char previous = (unsigned char)input[i - 1];
        unsigned char current = (unsigned char)input[i];

        if (is_lower_or_digit(previous) && is_upper(current)) {
            if (uppercase_count == SIZE_MAX) {
                return NULL;
            }
            ++uppercase_count;
        }
    }

    if (uppercase_count > SIZE_MAX - input_length - 1U) {
        return NULL;
    }

    output_length = input_length + uppercase_count;
    output = malloc(output_length + 1U);
    if (output == NULL) {
        return NULL;
    }

    for (i = 0; i < input_length; ++i) {
        unsigned char current = (unsigned char)input[i];

        if (i > 0 &&
            is_lower_or_digit((unsigned char)input[i - 1]) &&
            is_upper(current)) {
            output[j++] = '_';
        }

        output[j++] = input[i];
    }

    output[j] = '\0';
    return output;
}

int main(int argc, char *argv[])
{
    const char *input;
    char *result;
    size_t input_length = 0;

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        const char *program =
            argc > 0 && argv != NULL && argv[0] != NULL ? argv[0] : "program";

        fprintf(stderr, "Usage: %s <camelCaseString>\n", program);
        return EXIT_FAILURE;
    }

    input = argv[1];
    while (input[input_length] != '\0') {
        if (input_length == SIZE_MAX) {
            fputs("Input is too long\n", stderr);
            return EXIT_FAILURE;
        }
        ++input_length;
    }

    result = camel_to_snake(input, input_length);
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