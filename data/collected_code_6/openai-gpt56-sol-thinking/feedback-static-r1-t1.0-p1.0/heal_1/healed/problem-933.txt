#include <ctype.h>
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

char *camel_to_snake(const char *input, size_t input_length)
{
    size_t capacity;
    size_t output_position = 0;
    char *output;

    if (input == NULL) {
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
        int current_is_upper = current >= (unsigned char)'A' &&
                               current <= (unsigned char)'Z';

        if (current_is_upper && i > 0U) {
            unsigned char previous = (unsigned char)input[i - 1U];
            int next_is_lower =
                i + 1U < input_length &&
                islower((unsigned char)input[i + 1U]);

            if (islower(previous) ||
                isdigit(previous) ||
                (isupper(previous) && next_is_lower)) {
                output[output_position++] = '_';
            }
        }

        output[output_position++] = (char)tolower(current);
    }

    output[output_position] = '\0';
    return output;
}

static int get_string_length(const char *input, size_t *length)
{
    size_t position = 0;

    if (input == NULL || length == NULL) {
        errno = EINVAL;
        return -1;
    }

    while (input[position] != '\0') {
        if (position == SIZE_MAX - 1U) {
            errno = EOVERFLOW;
            return -1;
        }
        ++position;
    }

    *length = position;
    return 0;
}

int main(int argc, char *const argv[])
{
    const char *program_name;
    size_t input_length;
    char *result;

    program_name = argc > 0 && argv[0] != NULL ? argv[0] : "camel_to_snake";

    if (argc != 2 || argv[1] == NULL) {
        if (fprintf(stderr, "Usage: %s <camelCaseString>\n", program_name) < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (get_string_length(argv[1], &input_length) != 0) {
        perror("get_string_length");
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