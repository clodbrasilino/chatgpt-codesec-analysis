#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int remove_parenthesized(const char *input, size_t input_length, char **output)
{
    char *result;
    size_t write_index = 0;
    size_t depth = 0;

    if (input == NULL || output == NULL || input_length == SIZE_MAX) {
        return -1;
    }

    *output = NULL;

    result = malloc(input_length + 1);
    if (result == NULL) {
        return -1;
    }

    for (size_t read_index = 0; read_index < input_length; ++read_index) {
        unsigned char character = (unsigned char)input[read_index];

        if (character == '(') {
            if (depth == SIZE_MAX) {
                free(result);
                return -1;
            }
            ++depth;
        } else if (character == ')') {
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

static int read_line(FILE *stream, char **line, size_t *length)
{
    size_t capacity = 128;
    size_t used = 0;
    char *buffer;

    if (stream == NULL || line == NULL || length == NULL) {
        return -1;
    }

    *line = NULL;
    *length = 0;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    for (;;) {
        int character;

        if (used == capacity - 1) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return -1;
            }

            new_capacity = capacity * 2;
            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return -1;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        character = fgetc(stream);

        if (character == '\n') {
            break;
        }

        if (character == EOF) {
            if (ferror(stream) || used == 0) {
                free(buffer);
                return -1;
            }
            break;
        }

        buffer[used++] = (char)(unsigned char)character;
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
    size_t input_length = 0;

    if (read_line(stdin, &input, &input_length) != 0) {
        fputs("Failed to read input\n", stderr);
        return EXIT_FAILURE;
    }

    if (remove_parenthesized(input, input_length, &output) != 0) {
        free(input);
        fputs("Invalid input\n", stderr);
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