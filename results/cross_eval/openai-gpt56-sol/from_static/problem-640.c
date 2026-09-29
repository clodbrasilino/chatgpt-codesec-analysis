#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

enum { MAX_INPUT_LENGTH = 1024 * 1024 };

static int remove_parenthesized(const char *input, size_t length, char **output)
{
    char *result;
    size_t read_index;
    size_t write_index = 0;
    size_t depth = 0;

    if (input == NULL || output == NULL || length > MAX_INPUT_LENGTH) {
        return -1;
    }

    *output = NULL;

    if (length == SIZE_MAX) {
        return -1;
    }

    result = malloc(length + 1);
    if (result == NULL) {
        return -1;
    }

    for (read_index = 0; read_index < length; ++read_index) {
        if (input[read_index] == '(') {
            if (depth == SIZE_MAX) {
                free(result);
                return -1;
            }
            ++depth;
        } else if (input[read_index] == ')') {
            if (depth == 0) {
                free(result);
                return -1;
            }
            --depth;
        } else if (depth == 0) {
            result[write_index++] = input[read_index];
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
    char input[MAX_INPUT_LENGTH + 2];
    char *output = NULL;
    size_t length;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    for (length = 0; input[length] != '\0' && input[length] != '\n'; ++length) {
    }

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (length > MAX_INPUT_LENGTH) {
        fputs("Input is too long.\n", stderr);
        return EXIT_FAILURE;
    } else {
        int ch = fgetc(stdin);

        if (ch != '\n' && ch != EOF) {
            while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
            }
            fputs("Input is too long.\n", stderr);
            return EXIT_FAILURE;
        }

        if (ferror(stdin)) {
            return EXIT_FAILURE;
        }
    }

    if (remove_parenthesized(input, length, &output) != 0) {
        fputs("Invalid input or allocation failure.\n", stderr);
        return EXIT_FAILURE;
    }

    if (puts(output) == EOF) {
        free(output);
        return EXIT_FAILURE;
    }

    free(output);
    return EXIT_SUCCESS;
}