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
        if (input[read_index] == '(') {
            if (depth == SIZE_MAX) {
                free(result);
                return -1;
            }
            ++depth;
        } else if (input[read_index] == ')') {
            if (depth == 0U) {
                free(result);
                return -1;
            }
            --depth;
        } else if (depth == 0U) {
            if (write_index >= length) {
                free(result);
                return -1;
            }
            result[write_index++] = input[read_index];
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
    char discard_buffer[4096];

    if (stream == NULL) {
        return -1;
    }

    while (fgets(discard_buffer, sizeof discard_buffer, stream) != NULL) {
        size_t index;

        for (index = 0; discard_buffer[index] != '\0'; ++index) {
            if (discard_buffer[index] == '\n') {
                return 0;
            }
        }
    }

    return ferror(stream) ? -1 : 0;
}

static int read_line(FILE *stream, char **line, size_t *length)
{
    char *buffer;
    size_t used = 0;
    int character = EOF;

    if (stream == NULL || line == NULL || length == NULL) {
        return -1;
    }

    *line = NULL;
    *length = 0;

    buffer = malloc((size_t)MAX_INPUT_LENGTH + 1U);
    if (buffer == NULL) {
        return -1;
    }

    while (used < (size_t)MAX_INPUT_LENGTH) {
        character = fgetc(stream);

        if (character == EOF || character == '\n') {
            break;
        }

        buffer[used++] = (char)(unsigned char)character;
    }

    if (used == (size_t)MAX_INPUT_LENGTH) {
        character = fgetc(stream);

        if (character != '\n' && character != EOF) {
            if (discard_remaining_line(stream) != 0) {
                free(buffer);
                return -1;
            }

            free(buffer);
            return 1;
        }
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

    status = remove_parenthesized(input, length, &output);
    free(input);

    if (status != 0) {
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