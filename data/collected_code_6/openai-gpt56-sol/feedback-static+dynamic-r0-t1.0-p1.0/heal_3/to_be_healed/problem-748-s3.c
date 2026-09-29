#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int add_spaces_before_capitals(const char *input, size_t input_len,
                                      char **output)
{
    size_t extra_spaces = 0;
    size_t read_pos;
    size_t write_pos = 0;
    char *result;

    if (input == NULL || output == NULL) {
        return -1;
    }

    *output = NULL;

    for (read_pos = 1; read_pos < input_len; ++read_pos) {
        unsigned char previous = (unsigned char)input[read_pos - 1];
        unsigned char current = (unsigned char)input[read_pos];

        if (((previous >= 'a' && previous <= 'z') ||
             (previous >= '0' && previous <= '9')) &&
            current >= 'A' && current <= 'Z') {
            if (extra_spaces == SIZE_MAX) {
                return -1;
            }
            ++extra_spaces;
        }
    }

    if (extra_spaces > SIZE_MAX - input_len - 1U) {
        return -1;
    }

    result = malloc(input_len + extra_spaces + 1U);
    if (result == NULL) {
        return -1;
    }

    for (read_pos = 0; read_pos < input_len; ++read_pos) {
        unsigned char current = (unsigned char)input[read_pos];

        if (read_pos > 0) {
            unsigned char previous = (unsigned char)input[read_pos - 1];

            if (((previous >= 'a' && previous <= 'z') ||
                 (previous >= '0' && previous <= '9')) &&
                current >= 'A' && current <= 'Z') {
                result[write_pos++] = ' ';
            }
        }

        result[write_pos++] = input[read_pos];
    }

    result[write_pos] = '\0';
    *output = result;
    return 0;
}

static int read_line(FILE *stream, char **line, size_t *line_len)
{
    char *buffer;
    size_t length = 0;
    size_t capacity = 128U;
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

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stream)) != EOF && ch != '\n') {
        if (length == SIZE_MAX - 1U) {
            free(buffer);
            return -1;
        }

        if (length + 1U >= capacity) {
            size_t required = length + 2U;
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2U) {
                new_capacity = required;
            } else {
                new_capacity = capacity * 2U;
                if (new_capacity < required) {
                    new_capacity = required;
                }
            }

            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return -1;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    if (ferror(stream)) {
        free(buffer);
        return -1;
    }

    if (ch == EOF && length == 0U) {
        free(buffer);
        return 0;
    }

    buffer[length] = '\0';
    *line = buffer;
    *line_len = length;
    return 1;
}

int main(void)
{
    char *input;
    char *output = NULL;
    size_t length;
    int status;

    status = read_line(stdin, &input, &length);
    if (status < 0) {
        return EXIT_FAILURE;
    }

    if (status == 0) {
        return EXIT_SUCCESS;
    }

    if (add_spaces_before_capitals(input, length, &output) != 0) {
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