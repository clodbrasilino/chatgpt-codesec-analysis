#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int should_add_space(unsigned char previous, unsigned char current)
{
    return (((previous >= (unsigned char)'a' &&
              previous <= (unsigned char)'z') ||
             (previous >= (unsigned char)'0' &&
              previous <= (unsigned char)'9')) &&
            current >= (unsigned char)'A' &&
            current <= (unsigned char)'Z');
}

static int add_spaces_before_capitals(const char *input, size_t input_len,
                                      char **output)
{
    size_t extra_spaces = 0U;
    size_t read_pos;
    size_t write_pos = 0U;
    size_t allocation_size;
    char *result;

    if (input == NULL || output == NULL) {
        return -1;
    }

    *output = NULL;

    for (read_pos = 1U; read_pos < input_len; ++read_pos) {
        if (should_add_space((unsigned char)input[read_pos - 1U],
                             (unsigned char)input[read_pos])) {
            if (extra_spaces == SIZE_MAX) {
                return -1;
            }
            ++extra_spaces;
        }
    }

    if (input_len > SIZE_MAX - extra_spaces) {
        return -1;
    }

    allocation_size = input_len + extra_spaces;

    if (allocation_size == SIZE_MAX) {
        return -1;
    }

    ++allocation_size;

    result = malloc(allocation_size);
    if (result == NULL) {
        return -1;
    }

    for (read_pos = 0U; read_pos < input_len; ++read_pos) {
        if (read_pos > 0U &&
            should_add_space((unsigned char)input[read_pos - 1U],
                             (unsigned char)input[read_pos])) {
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
    char *buffer;
    size_t length = 0U;
    size_t capacity = 128U;

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

        if (length >= capacity - 1U) {
            size_t required;
            size_t new_capacity;
            char *resized;

            if (length > SIZE_MAX - 2U) {
                free(buffer);
                return -1;
            }

            required = length + 2U;

            if (capacity <= SIZE_MAX / 2U) {
                new_capacity = capacity * 2U;
            } else {
                new_capacity = required;
            }

            if (new_capacity < required) {
                new_capacity = required;
            }

            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return -1;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
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

    if (length == 0U && feof(stream)) {
        free(buffer);
        return 0;
    }

    if (length > 0U && buffer[length - 1U] == '\r') {
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
    size_t length = 0U;
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