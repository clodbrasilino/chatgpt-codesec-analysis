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
    size_t write_pos = 0U;

    if (input == NULL || output == NULL) {
        return -1;
    }

    *output = NULL;

    if (input_len > (SIZE_MAX - 1U) / 2U) {
        return -1;
    }

    capacity = input_len * 2U + 1U;
    result = malloc(capacity);
    if (result == NULL) {
        return -1;
    }

    for (read_pos = 0U; read_pos < input_len; ++read_pos) {
        unsigned char current = (unsigned char)input[read_pos];

        if (isupper(current) != 0 &&
            read_pos > 0U &&
            input[read_pos - 1U] != ' ') {
            result[write_pos++] = ' ';
        }

        result[write_pos++] = input[read_pos];
    }

    result[write_pos] = '\0';
    *output = result;
    return 0;
}

static int read_line(FILE *stream, char **line, size_t *line_length)
{
    char *buffer;
    size_t capacity = 128U;
    size_t length = 0U;
    int ch;

    if (stream == NULL || line == NULL || line_length == NULL) {
        return -1;
    }

    *line = NULL;
    *line_length = 0U;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    while ((ch = fgetc(stream)) != EOF && ch != '\n') {
        if (length == SIZE_MAX - 1U) {
            free(buffer);
            return -1;
        }

        if (length + 1U >= capacity) {
            char *resized;
            size_t new_capacity;

            if (capacity > SIZE_MAX / 2U) {
                free(buffer);
                return -1;
            }

            new_capacity = capacity * 2U;
            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return -1;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[length++] = (char)(unsigned char)ch;
    }

    if (ch == EOF && (ferror(stream) != 0 || length == 0U)) {
        free(buffer);
        return -1;
    }

    if (length > 0U && buffer[length - 1U] == '\r') {
        --length;
    }

    buffer[length] = '\0';
    *line = buffer;
    *line_length = length;
    return 0;
}

int main(void)
{
    char *input = NULL;
    char *output = NULL;
    size_t input_length = 0U;
    int exit_status = EXIT_FAILURE;

    if (read_line(stdin, &input, &input_length) != 0) {
        goto cleanup;
    }

    if (add_spaces_before_capitals(input, input_length, &output) != 0) {
        goto cleanup;
    }

    if (puts(output) == EOF) {
        goto cleanup;
    }

    exit_status = EXIT_SUCCESS;

cleanup:
    free(output);
    free(input);
    return exit_status;
}