#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int get_input_length(const char *input, size_t *length)
{
    size_t position = 0;

    if (input == NULL || length == NULL) {
        errno = EINVAL;
        return -1;
    }

    while (input[position] != '\0') {
        if (position >= (SIZE_MAX - 1U) / 2U) {
            errno = EOVERFLOW;
            return -1;
        }
        ++position;
    }

    *length = position;
    return 0;
}

static int is_ascii_lower(unsigned char character)
{
    return character >= (unsigned char)'a' &&
           character <= (unsigned char)'z';
}

static int is_ascii_upper(unsigned char character)
{
    return character >= (unsigned char)'A' &&
           character <= (unsigned char)'Z';
}

static int is_ascii_digit(unsigned char character)
{
    return character >= (unsigned char)'0' &&
           character <= (unsigned char)'9';
}

static unsigned char ascii_to_lower(unsigned char character)
{
    if (is_ascii_upper(character)) {
        return (unsigned char)(character - (unsigned char)'A' +
                               (unsigned char)'a');
    }

    return character;
}

char *camel_to_snake(const char *input, size_t input_length)
{
    size_t capacity;
    size_t output_position = 0;
    char *output;

    if (input == NULL) {
        errno = EINVAL;
        return NULL;
    }

    if (memchr(input, '\0', input_length) != NULL) {
        errno = EINVAL;
        return NULL;
    }

    if (input_length > (SIZE_MAX - 1U) / 2U) {
        errno = EOVERFLOW;
        return NULL;
    }

    capacity = input_length * 2U + 1U;
    output = malloc(capacity);
    if (output == NULL) {
        errno = ENOMEM;
        return NULL;
    }

    for (size_t i = 0; i < input_length; ++i) {
        unsigned char current = (unsigned char)input[i];

        if (is_ascii_upper(current) && i > 0U) {
            unsigned char previous = (unsigned char)input[i - 1U];
            int next_is_lower =
                i + 1U < input_length &&
                is_ascii_lower((unsigned char)input[i + 1U]);

            if (is_ascii_lower(previous) ||
                is_ascii_digit(previous) ||
                (is_ascii_upper(previous) && next_is_lower)) {
                output[output_position++] = '_';
            }
        }

        output[output_position++] = (char)ascii_to_lower(current);
    }

    output[output_position] = '\0';
    return output;
}

int main(int argc, char *argv[])
{
    const char *program_name;
    size_t input_length;
    char *result;

    program_name =
        argc > 0 && argv != NULL && argv[0] != NULL
            ? argv[0]
            : "camel_to_snake";

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s <camelCaseString>\n", program_name);
        return EXIT_FAILURE;
    }

    if (get_input_length(argv[1], &input_length) != 0) {
        perror("camel_to_snake");
        return EXIT_FAILURE;
    }

    result = camel_to_snake(argv[1], input_length);
    if (result == NULL) {
        perror("camel_to_snake");
        return EXIT_FAILURE;
    }

    if (printf("%s\n", result) < 0) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}