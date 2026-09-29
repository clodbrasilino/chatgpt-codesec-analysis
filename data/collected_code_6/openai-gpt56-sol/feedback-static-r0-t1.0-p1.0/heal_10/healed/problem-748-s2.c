#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int add_spaces_before_capitals(const char *input, size_t input_len,
                                      char **output)
{
    char *result;
    size_t capacity;
    size_t read_pos;
    size_t write_pos = 0;

    if (input == NULL || output == NULL) {
        return -1;
    }

    *output = NULL;

    if (input_len > (SIZE_MAX - 1) / 2) {
        return -1;
    }

    capacity = input_len * 2 + 1;
    result = malloc(capacity);
    if (result == NULL) {
        return -1;
    }

    for (read_pos = 0; read_pos < input_len; ++read_pos) {
        unsigned char ch = (unsigned char)input[read_pos];

        if (isupper(ch) != 0 &&
            read_pos != 0 &&
            input[read_pos - 1] != ' ') {
            result[write_pos++] = ' ';
        }

        result[write_pos++] = (char)ch;
    }

    result[write_pos] = '\0';
    *output = result;
    return 0;
}

static int read_line(FILE *stream, char **line, size_t *line_len)
{
    char *buffer;
    size_t length = 0;
    size_t capacity = 128;

    if (stream == NULL || line == NULL || line_len == NULL) {
        return -1;
    }

    *line = NULL;
    *line_len = 0;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    for (;;) {
        int ch;

        if (length == capacity - 1) {
            char *resized;
            size_t new_capacity;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return -1;
            }

            new_capacity = capacity * 2;
            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return -1;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        ch = fgetc(stream);

        if (ch == EOF) {
            if (ferror(stream)) {
                free(buffer);
                return -1;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        buffer[length++] = (char)(unsigned char)ch;
    }

    if (length > 0 && buffer[length - 1] == '\r') {
        --length;
    }

    buffer[length] = '\0';
    *line = buffer;
    *line_len = length;
    return 0;
}

int main(void)
{
    char *input = NULL;
    char *output = NULL;
    size_t input_len = 0;
    int status = EXIT_FAILURE;

    if (read_line(stdin, &input, &input_len) != 0) {
        fputs("Failed to read input.\n", stderr);
        goto cleanup;
    }

    if (add_spaces_before_capitals(input, input_len, &output) != 0) {
        fputs("Failed to process input.\n", stderr);
        goto cleanup;
    }

    if (puts(output) == EOF) {
        fputs("Failed to write output.\n", stderr);
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(output);
    free(input);
    return status;
}