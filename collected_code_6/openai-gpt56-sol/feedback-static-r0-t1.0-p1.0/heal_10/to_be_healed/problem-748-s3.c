#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int is_lower_or_digit(unsigned char ch)
{
    return (ch >= (unsigned char)'a' && ch <= (unsigned char)'z') ||
           (ch >= (unsigned char)'0' && ch <= (unsigned char)'9');
}

static int is_upper(unsigned char ch)
{
    return ch >= (unsigned char)'A' && ch <= (unsigned char)'Z';
}

static int grow_buffer(char **buffer, size_t *capacity, size_t required)
{
    size_t new_capacity;
    char *new_buffer;

    if (buffer == NULL || capacity == NULL || *buffer == NULL) {
        return -1;
    }

    if (required <= *capacity) {
        return 0;
    }

    new_capacity = *capacity;

    if (new_capacity == 0U) {
        new_capacity = 1U;
    }

    while (new_capacity < required) {
        if (new_capacity > SIZE_MAX / 2U) {
            new_capacity = required;
            break;
        }

        new_capacity *= 2U;
    }

    new_buffer = realloc(*buffer, new_capacity);
    if (new_buffer == NULL) {
        return -1;
    }

    *buffer = new_buffer;
    *capacity = new_capacity;
    return 0;
}

static int read_line(FILE *stream, char **line, size_t *length)
{
    size_t capacity = 128U;
    size_t used = 0U;
    char *buffer;
    int ch = EOF;

    if (stream == NULL || line == NULL || length == NULL) {
        return -1;
    }

    *line = NULL;
    *length = 0U;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stream);

        if (ch == EOF || ch == '\n') {
            break;
        }

        if (used > SIZE_MAX - 2U) {
            free(buffer);
            return -1;
        }

        if (grow_buffer(&buffer, &capacity, used + 2U) != 0) {
            free(buffer);
            return -1;
        }

        buffer[used] = (char)(unsigned char)ch;
        ++used;
    }

    if (ch == EOF) {
        if (ferror(stream)) {
            free(buffer);
            return -1;
        }

        if (used == 0U) {
            free(buffer);
            return 0;
        }
    }

    buffer[used] = '\0';
    *line = buffer;
    *length = used;
    return 1;
}

static int add_spaces_before_capitals(const char *input, size_t input_len,
                                      char **output, size_t *output_len)
{
    size_t extra_spaces = 0U;
    size_t read_pos;
    size_t write_pos = 0U;
    size_t result_len;
    char *result;

    if (input == NULL || output == NULL || output_len == NULL) {
        return -1;
    }

    *output = NULL;
    *output_len = 0U;

    for (read_pos = 1U; read_pos < input_len; ++read_pos) {
        unsigned char previous = (unsigned char)input[read_pos - 1U];
        unsigned char current = (unsigned char)input[read_pos];

        if (is_lower_or_digit(previous) && is_upper(current)) {
            if (extra_spaces == SIZE_MAX) {
                return -1;
            }

            ++extra_spaces;
        }
    }

    if (input_len > SIZE_MAX - extra_spaces) {
        return -1;
    }

    result_len = input_len + extra_spaces;

    if (result_len == SIZE_MAX) {
        return -1;
    }

    result = malloc(result_len + 1U);
    if (result == NULL) {
        return -1;
    }

    for (read_pos = 0U; read_pos < input_len; ++read_pos) {
        unsigned char current = (unsigned char)input[read_pos];

        if (read_pos != 0U) {
            unsigned char previous = (unsigned char)input[read_pos - 1U];

            if (is_lower_or_digit(previous) && is_upper(current)) {
                result[write_pos++] = ' ';
            }
        }

        result[write_pos++] = input[read_pos];
    }

    result[write_pos] = '\0';
    *output = result;
    *output_len = write_pos;
    return 0;
}

static int write_all(FILE *stream, const char *buffer, size_t length)
{
    size_t written = 0U;

    if (stream == NULL || (buffer == NULL && length != 0U)) {
        return -1;
    }

    while (written < length) {
        size_t count = fwrite(buffer + written, 1U, length - written, stream);

        if (count == 0U) {
            return -1;
        }

        written += count;
    }

    return 0;
}

int main(void)
{
    char *input = NULL;
    char *output = NULL;
    size_t input_len = 0U;
    size_t output_len = 0U;
    int status;
    int result = EXIT_FAILURE;

    status = read_line(stdin, &input, &input_len);
    if (status < 0) {
        goto cleanup;
    }

    if (status == 0) {
        result = EXIT_SUCCESS;
        goto cleanup;
    }

    if (add_spaces_before_capitals(input, input_len, &output,
                                   &output_len) != 0) {
        goto cleanup;
    }

    if (write_all(stdout, output, output_len) != 0) {
        goto cleanup;
    }

    if (fputc('\n', stdout) == EOF) {
        goto cleanup;
    }

    if (fflush(stdout) == EOF) {
        goto cleanup;
    }

    result = EXIT_SUCCESS;

cleanup:
    free(output);
    free(input);
    return result;
}