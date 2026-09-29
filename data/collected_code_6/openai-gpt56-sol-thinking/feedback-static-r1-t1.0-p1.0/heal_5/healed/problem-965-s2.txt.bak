#include <ctype.h>
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int needs_separator(const char *input, size_t index, size_t length)
{
    unsigned char current;
    unsigned char previous;

    if (index == 0U) {
        return 0;
    }

    current = (unsigned char)input[index];
    previous = (unsigned char)input[index - 1U];

    if (!isupper(current) || previous == (unsigned char)'_') {
        return 0;
    }

    if (islower(previous) || isdigit(previous)) {
        return 1;
    }

    if (isupper(previous) && index + 1U < length) {
        unsigned char next = (unsigned char)input[index + 1U];
        return islower(next) != 0;
    }

    return 0;
}

char *camel_to_snake(const char *input)
{
    size_t input_length;
    size_t output_length = 0U;
    size_t output_index = 0U;
    char *output;

    if (input == NULL) {
        errno = EINVAL;
        return NULL;
    }

    input_length = strlen(input);

    for (size_t i = 0U; i < input_length; ++i) {
        size_t required = needs_separator(input, i, input_length) ? 2U : 1U;

        if (output_length > SIZE_MAX - required) {
            errno = EOVERFLOW;
            return NULL;
        }

        output_length += required;
    }

    if (output_length == SIZE_MAX) {
        errno = EOVERFLOW;
        return NULL;
    }

    output = malloc(output_length + 1U);
    if (output == NULL) {
        errno = ENOMEM;
        return NULL;
    }

    for (size_t i = 0U; i < input_length; ++i) {
        unsigned char current = (unsigned char)input[i];

        if (needs_separator(input, i, input_length)) {
            output[output_index++] = '_';
        }

        output[output_index++] = (char)tolower(current);
    }

    output[output_index] = '\0';
    return output;
}

int main(int argc, char *const argv[])
{
    char *result;

    if (argc != 2) {
        fputs("Usage: camel_to_snake <string>\n", stderr);
        return EXIT_FAILURE;
    }

    result = camel_to_snake(argv[1]);
    if (result == NULL) {
        perror("camel_to_snake");
        return EXIT_FAILURE;
    }

    if (puts(result) == EOF) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}