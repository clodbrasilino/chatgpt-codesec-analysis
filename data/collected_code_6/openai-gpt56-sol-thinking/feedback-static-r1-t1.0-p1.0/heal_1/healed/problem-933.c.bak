#include <ctype.h>
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *camel_to_snake(const char *input)
{
    size_t input_length;
    size_t output_capacity;
    size_t output_position = 0;
    char *output;

    if (input == NULL) {
        errno = EINVAL;
        return NULL;
    }

    input_length = strlen(input);

    if (input_length > (SIZE_MAX - 1U) / 2U) {
        errno = EOVERFLOW;
        return NULL;
    }

    output_capacity = input_length * 2U + 1U;
    output = malloc(output_capacity);

    if (output == NULL) {
        errno = ENOMEM;
        return NULL;
    }

    for (size_t position = 0; position < input_length; ++position) {
        unsigned char current = (unsigned char)input[position];

        if (isupper(current)) {
            int insert_separator = 0;

            if (position > 0U) {
                unsigned char previous =
                    (unsigned char)input[position - 1U];
                int next_is_lower =
                    position + 1U < input_length &&
                    islower((unsigned char)input[position + 1U]);

                insert_separator =
                    islower(previous) ||
                    isdigit(previous) ||
                    (isupper(previous) && next_is_lower);
            }

            if (insert_separator) {
                output[output_position++] = '_';
            }
        }

        output[output_position++] = (char)tolower(current);
    }

    output[output_position] = '\0';
    return output;
}

int main(int argc, char * const argv[])
{
    const char *program_name;
    char *result;

    program_name =
        argc > 0 && argv[0] != NULL ? argv[0] : "camel_to_snake";

    if (argc != 2) {
        if (fprintf(
                stderr,
                "Usage: %s <camelCaseString>\n",
                program_name
            ) < 0) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    result = camel_to_snake(argv[1]);

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