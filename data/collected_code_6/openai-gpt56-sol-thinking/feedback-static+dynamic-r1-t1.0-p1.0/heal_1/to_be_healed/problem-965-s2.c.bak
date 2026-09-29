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
    /* Possible weaknesses found:
     *  The scope of the variable 'next' can be reduced. [variableScope]
     */
    unsigned char next;

    if (index == 0) {
        return 0;
    }

    current = (unsigned char)input[index];
    previous = (unsigned char)input[index - 1];

    if (!isupper(current) || previous == '_') {
        return 0;
    }

    if (islower(previous) || isdigit(previous)) {
        return 1;
    }

    if (isupper(previous) && index + 1 < length) {
        next = (unsigned char)input[index + 1];
        return islower(next) != 0;
    }

    return 0;
}

char *camel_to_snake(const char *input)
{
    size_t input_length;
    size_t output_length = 0;
    size_t input_index;
    size_t output_index = 0;
    char *output;

    if (input == NULL) {
        errno = EINVAL;
        return NULL;
    }

    input_length = strlen(input);

    for (input_index = 0; input_index < input_length; ++input_index) {
        if (needs_separator(input, input_index, input_length)) {
            if (output_length == SIZE_MAX) {
                errno = EOVERFLOW;
                return NULL;
            }
            ++output_length;
        }

        if (output_length == SIZE_MAX) {
            errno = EOVERFLOW;
            return NULL;
        }
        ++output_length;
    }

    if (output_length == SIZE_MAX) {
        errno = EOVERFLOW;
        return NULL;
    }

    output = malloc(output_length + 1);
    if (output == NULL) {
        errno = ENOMEM;
        return NULL;
    }

    for (input_index = 0; input_index < input_length; ++input_index) {
        unsigned char current = (unsigned char)input[input_index];

        if (needs_separator(input, input_index, input_length)) {
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
int main(int argc, char *argv[])
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