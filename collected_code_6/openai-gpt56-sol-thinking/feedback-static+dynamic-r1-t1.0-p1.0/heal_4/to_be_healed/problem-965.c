#include <ctype.h>
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int needs_separator(const char *input, size_t index)
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
    next = (unsigned char)input[index + 1];

    return islower(previous) || isdigit(previous) ||
           (isupper(previous) && islower(next));
}

char *camel_to_snake(const char *input)
{
    char *output;
    size_t input_index;
    size_t output_index = 0;
    size_t output_length = 0;

    if (input == NULL) {
        errno = EINVAL;
        return NULL;
    }

    for (input_index = 0; input[input_index] != '\0'; ++input_index) {
        size_t required = needs_separator(input, input_index) ? 2U : 1U;

        if (output_length > SIZE_MAX - required) {
            errno = ERANGE;
            return NULL;
        }

        output_length += required;
    }

    if (output_length == SIZE_MAX) {
        errno = ERANGE;
        return NULL;
    }

    output = malloc(output_length + 1U);
    if (output == NULL) {
        errno = ENOMEM;
        return NULL;
    }

    for (input_index = 0; input[input_index] != '\0'; ++input_index) {
        unsigned char current = (unsigned char)input[input_index];

        if (needs_separator(input, input_index)) {
            output[output_index++] = '_';
        }

        output[output_index++] = (char)tolower(current);
    }

    output[output_index] = '\0';
    return output;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    char *snake_case;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <camel-case-string>\n", argv[0]);
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