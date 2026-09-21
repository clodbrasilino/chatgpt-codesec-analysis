#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int remove_lowercase_substrings(const char *input, size_t input_len,
                                       char **output)
{
    char *result;
    size_t read_pos;
    size_t write_pos = 0;

    if (input == NULL || output == NULL || input_len == SIZE_MAX) {
        return -1;
    }

    *output = NULL;

    result = malloc(input_len + 1);
    if (result == NULL) {
        return -1;
    }

    for (read_pos = 0; read_pos < input_len; ++read_pos) {
        unsigned char ch = (unsigned char)input[read_pos];

        if (ch < (unsigned char)'a' || ch > (unsigned char)'z') {
            result[write_pos++] = (char)ch;
        }
    }

    result[write_pos] = '\0';
    *output = result;
    return 0;
}

static int read_line(FILE *stream, char **line, size_t *line_len)
{
    char *buffer = NULL;
    size_t capacity = 128;
    size_t length = 0;
    int ch;

    if (stream == NULL || line == NULL || line_len == NULL) {
        return -1;
    }

    *line = NULL;
    *line_len = 0;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    while ((ch = fgetc(stream)) != EOF && ch != '\n') {
        if (length >= capacity - 1) {
            char *new_buffer;
            size_t new_capacity;

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

        buffer[length++] = (char)(unsigned char)ch;
    }

    if (ch == EOF) {
        if (ferror(stream)) {
            free(buffer);
            return -1;
        }

        if (length == 0) {
            free(buffer);
            return 0;
        }
    }

    if (length > 0 && buffer[length - 1] == '\r') {
        --length;
    }

    buffer[length] = '\0';
    *line = buffer;
    *line_len = length;
    return 1;
}

int main(void)
{
    char *input = NULL;
    char *output = NULL;
    size_t input_len = 0;
    int status;

    status = read_line(stdin, &input, &input_len);
    if (status < 0) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (status == 0) {
        return EXIT_SUCCESS;
    }

    if (remove_lowercase_substrings(input, input_len, &output) != 0) {
        free(input);
        fputs("Failed to process input.\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    if (puts(output) == EOF) {
        free(output);
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    free(output);
    return EXIT_SUCCESS;
}