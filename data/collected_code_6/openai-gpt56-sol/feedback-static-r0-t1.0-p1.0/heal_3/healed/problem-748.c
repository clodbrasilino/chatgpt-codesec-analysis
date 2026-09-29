#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int add_spaces_before_capitals(const char *input, size_t input_len,
                                      char **output)
{
    size_t extra = 0U;
    size_t capacity;
    size_t read_pos;
    size_t write_pos = 0U;
    char *result;

    if (input == NULL || output == NULL) {
        return -1;
    }

    *output = NULL;

    for (read_pos = 0U; read_pos < input_len; ++read_pos) {
        if (isupper((unsigned char)input[read_pos]) &&
            read_pos > 0U &&
            input[read_pos - 1U] != ' ') {
            if (extra == SIZE_MAX) {
                return -1;
            }
            ++extra;
        }
    }

    if (extra > SIZE_MAX - input_len ||
        input_len + extra > SIZE_MAX - 1U) {
        return -1;
    }

    capacity = input_len + extra + 1U;
    result = malloc(capacity);
    if (result == NULL) {
        return -1;
    }

    for (read_pos = 0U; read_pos < input_len; ++read_pos) {
        if (isupper((unsigned char)input[read_pos]) &&
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

static int read_line(FILE *stream, char **line, size_t *line_len)
{
    size_t capacity = 128U;
    size_t length = 0U;
    char *buffer;

    if (stream == NULL || line == NULL || line_len == NULL) {
        return -1;
    }

    *line = NULL;
    *line_len = 0U;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    for (;;) {
        int ch = fgetc(stream);

        if (ch == EOF) {
            if (ferror(stream)) {
                free(buffer);
                return -1;
            }

            if (length == 0U) {
                free(buffer);
                return 1;
            }

            break;
        }

        if (ch == '\n') {
            break;
        }

        if (length >= capacity - 1U) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2U) {
                free(buffer);
                return -1;
            }

            new_capacity = capacity * 2U;
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

    buffer[length] = '\0';
    *line = buffer;
    *line_len = length;
    return 0;
}

int main(void)
{
    char *input = NULL;
    char *output = NULL;
    size_t input_len = 0U;
    int status;

    status = read_line(stdin, &input, &input_len);
    if (status != 0) {
        return status == 1 ? EXIT_SUCCESS : EXIT_FAILURE;
    }

    if (add_spaces_before_capitals(input, input_len, &output) != 0) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);

    if (fputs(output, stdout) == EOF || fputc('\n', stdout) == EOF) {
        free(output);
        return EXIT_FAILURE;
    }

    free(output);
    return EXIT_SUCCESS;
}