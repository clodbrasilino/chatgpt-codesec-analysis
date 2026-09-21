#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int remove_parenthesized(const char *input, size_t length, char **output)
{
    char *result;
    size_t read_index;
    size_t write_index = 0;
    size_t depth = 0;

    if (input == NULL || output == NULL || length == SIZE_MAX) {
        return -1;
    }

    *output = NULL;

    result = malloc(length + 1);
    if (result == NULL) {
        return -1;
    }

    for (read_index = 0; read_index < length; ++read_index) {
        unsigned char character = (unsigned char)input[read_index];

        if (character == (unsigned char)'(') {
            if (depth == SIZE_MAX) {
                free(result);
                return -1;
            }
            ++depth;
        } else if (character == (unsigned char)')') {
            if (depth == 0) {
                free(result);
                return -1;
            }
            --depth;
        } else if (depth == 0) {
            result[write_index++] = (char)character;
        }
    }

    if (depth != 0) {
        free(result);
        return -1;
    }

    result[write_index] = '\0';
    *output = result;
    return 0;
}

int main(void)
{
    enum { MAX_INPUT_LENGTH = 1048576 };
    char *input;
    char *output = NULL;
    size_t length;

    input = malloc((size_t)MAX_INPUT_LENGTH + 2);
    if (input == NULL) {
        return EXIT_FAILURE;
    }

    if (fgets(input, MAX_INPUT_LENGTH + 2, stdin) == NULL) {
        if (ferror(stdin)) {
            free(input);
            return EXIT_FAILURE;
        }
        input[0] = '\0';
    }

    length = 0;
    while (input[length] != '\0' && input[length] != '\n') {
        ++length;
    }

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (length == (size_t)MAX_INPUT_LENGTH + 1) {
        fputs("Input too long\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    if (remove_parenthesized(input, length, &output) != 0) {
        fputs("Invalid input\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    if (puts(output) == EOF) {
        free(output);
        free(input);
        return EXIT_FAILURE;
    }

    free(output);
    free(input);
    return EXIT_SUCCESS;
}