#include <ctype.h>
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int needs_separator(const char *input, size_t length, size_t index)
{
    unsigned char current;
    unsigned char previous;
    unsigned char next;

    if (index == 0 || input[index - 1] == '_') {
        return 0;
    }

    current = (unsigned char)input[index];
    if (!isupper(current)) {
        return 0;
    }

    previous = (unsigned char)input[index - 1];
    next = index + 1 < length
        ? (unsigned char)input[index + 1]
        : (unsigned char)'\0';

    return islower(previous) ||
           isdigit(previous) ||
           (isupper(previous) && islower(next));
}

char *camel_to_snake(const char *input)
{
    char *output;
    size_t input_length;
    size_t output_length;
    size_t input_index;
    size_t output_index;

    if (input == NULL) {
        errno = EINVAL;
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    input_length = strlen(input);
    output_length = input_length;

    for (input_index = 0; input_index < input_length; ++input_index) {
        if (needs_separator(input, input_length, input_index)) {
            if (output_length == SIZE_MAX) {
                errno = ERANGE;
                return NULL;
            }
            ++output_length;
        }
    }

    if (output_length == SIZE_MAX) {
        errno = ERANGE;
        return NULL;
    }

    output = malloc(output_length + 1);
    if (output == NULL) {
        errno = ENOMEM;
        return NULL;
    }

    output_index = 0;

    for (input_index = 0; input_index < input_length; ++input_index) {
        unsigned char current = (unsigned char)input[input_index];

        if (needs_separator(input, input_length, input_index)) {
            output[output_index++] = '_';
        }

        output[output_index++] = (char)tolower(current);
    }

    output[output_index] = '\0';
    return output;
}

int main(int argc, char **const argv)
{
    char *snake_case;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <camel-case-string>\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "camel_to_snake");
        return EXIT_FAILURE;
    }

    snake_case = camel_to_snake(argv[1]);
    if (snake_case == NULL) {
        int error_code = errno;
        fprintf(stderr, "Conversion failed: %s\n", strerror(error_code));
        return EXIT_FAILURE;
    }

    if (puts(snake_case) == EOF) {
        free(snake_case);
        return EXIT_FAILURE;
    }

    free(snake_case);
    return EXIT_SUCCESS;
}