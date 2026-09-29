#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int add_spaces_before_capitals(const char *input, size_t input_len,
                                      char **output)
{
    size_t extra = 0U;
    size_t read_pos;
    size_t write_pos = 0U;
    char *result;

    if (input == NULL || output == NULL) {
        return -1;
    }

    *output = NULL;

    for (read_pos = 0U; read_pos < input_len; ++read_pos) {
        unsigned char current = (unsigned char)input[read_pos];

        if (read_pos > 0U &&
            isupper(current) != 0 &&
            input[read_pos - 1U] != ' ') {
            if (extra == SIZE_MAX) {
                return -1;
            }
            ++extra;
        }
    }

    if (input_len > SIZE_MAX - extra ||
        input_len + extra == SIZE_MAX) {
        return -1;
    }

    result = malloc(input_len + extra + 1U);
    if (result == NULL) {
        return -1;
    }

    for (read_pos = 0U; read_pos < input_len; ++read_pos) {
        unsigned char current = (unsigned char)input[read_pos];

        if (read_pos > 0U &&
            isupper(current) != 0 &&
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
        int ch;

        if (length == capacity - 1U) {
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

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stream);

        if (ch == EOF) {
            if (ferror(stream) != 0) {
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
    if (status == 1) {
        return EXIT_SUCCESS;
    }

    if (status != 0) {
        return EXIT_FAILURE;
    }

    if (add_spaces_before_capitals(input, input_len, &output) != 0) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);

    if (fputs(output, stdout) == EOF ||
        fputc('\n', stdout) == EOF) {
        free(output);
        return EXIT_FAILURE;
    }

    free(output);
    return EXIT_SUCCESS;
}