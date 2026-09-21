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
        switch (input[read_index]) {
        case '(':
            if (depth == SIZE_MAX) {
                free(result);
                return -1;
            }
            ++depth;
            break;

        case ')':
            if (depth == 0) {
                free(result);
                return -1;
            }
            --depth;
            break;

        default:
            if (depth == 0) {
                result[write_index++] = input[read_index];
            }
            break;
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

static int read_line(char **line, size_t *length)
{
    char *buffer;
    size_t used = 0;
    int ch;

    if (line == NULL || length == NULL) {
        return -1;
    }

    *line = NULL;
    *length = 0;

    buffer = malloc((size_t)MAX_INPUT_LENGTH + 1);
    if (buffer == NULL) {
        return -1;
    }

    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (used == MAX_INPUT_LENGTH) {
            do {
                ch = getchar();
            } while (ch != '\n' && ch != EOF);

            free(buffer);

            if (ferror(stdin)) {
                return -1;
            }

            return 1;
        }

        buffer[used++] = (char)ch;
    }

    if (ferror(stdin) || (ch == EOF && used == 0)) {
        free(buffer);
        return -1;
    }

    buffer[used] = '\0';
    *line = buffer;
    *length = used;
    return 0;
}

int main(void)
{
    char *input = NULL;
    char *output = NULL;
    size_t length = 0;
    int status;

    status = read_line(&input, &length);
    if (status != 0) {
        if (status > 0) {
            fputs("Input is too long.\n", stderr);
        }
        return EXIT_FAILURE;
    }

    if (remove_parenthesized(input, length, &output) != 0) {
        fputs("Invalid input or allocation failure.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    free(input);

    if (puts(output) == EOF) {
        free(output);
        return EXIT_FAILURE;
    }

    free(output);
    return EXIT_SUCCESS;
}