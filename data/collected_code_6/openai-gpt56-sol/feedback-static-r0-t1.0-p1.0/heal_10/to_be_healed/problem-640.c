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

    if (input == NULL || output == NULL ||
        length > (size_t)MAX_INPUT_LENGTH ||
        length == SIZE_MAX) {
        return -1;
    }

    *output = NULL;

    result = malloc(length + 1U);
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
            if (depth == 0U) {
                free(result);
                return -1;
            }
            --depth;
            break;

        default:
            if (depth == 0U) {
                result[write_index++] = input[read_index];
            }
            break;
        }
    }

    if (depth != 0U) {
        free(result);
        return -1;
    }

    result[write_index] = '\0';
    *output = result;
    return 0;
}

static int discard_remaining_line(FILE *stream)
{
    int character;

    if (stream == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stream)) != '\n' && character != EOF) {
    }

    return ferror(stream) ? -1 : 0;
}

static int read_line(FILE *stream, char **line, size_t *length)
{
    char *buffer;
    size_t used = 0;
    int character;

    if (stream == NULL || line == NULL || length == NULL) {
        return -1;
    }

    *line = NULL;
    *length = 0;

    buffer = malloc((size_t)MAX_INPUT_LENGTH + 1U);
    if (buffer == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stream)) != EOF) {
        if (character == '\n') {
            break;
        }

        if (used == (size_t)MAX_INPUT_LENGTH) {
            if (discard_remaining_line(stream) != 0) {
                free(buffer);
                return -1;
            }

            free(buffer);
            return 1;
        }

        buffer[used++] = (char)character;
    }

    if (ferror(stream) || (character == EOF && used == 0U)) {
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

    status = read_line(stdin, &input, &length);
    if (status != 0) {
        if (status > 0) {
            fputs("Input is too long.\n", stderr);
        } else {
            fputs("Unable to read input.\n", stderr);
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