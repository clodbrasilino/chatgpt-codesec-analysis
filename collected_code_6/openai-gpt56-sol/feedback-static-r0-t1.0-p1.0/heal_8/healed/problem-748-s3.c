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

static int add_spaces_before_capitals(const char *input, size_t input_len,
                                      char **output, size_t *output_len)
{
    size_t extra_spaces = 0;
    size_t read_pos;
    size_t write_pos = 0;
    size_t result_len;
    char *result;

    if (input == NULL || output == NULL || output_len == NULL) {
        return -1;
    }

    *output = NULL;
    *output_len = 0;

    for (read_pos = 1; read_pos < input_len; ++read_pos) {
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

    for (read_pos = 0; read_pos < input_len; ++read_pos) {
        unsigned char current = (unsigned char)input[read_pos];

        if (read_pos > 0U) {
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

static int grow_buffer(char **buffer, size_t *capacity, size_t required)
{
    size_t new_capacity;
    char *new_buffer;

    if (buffer == NULL || *buffer == NULL || capacity == NULL) {
        return -1;
    }

    if (required <= *capacity) {
        return 0;
    }

    new_capacity = *capacity;

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
    size_t used = 0;
    char *buffer;
    int ch;

    if (stream == NULL || line == NULL || length == NULL) {
        return -1;
    }

    *line = NULL;
    *length = 0;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    while ((ch = fgetc(stream)) != EOF) {
        if (ch == '\n') {
            break;
        }

        if (used == SIZE_MAX - 1U) {
            free(buffer);
            return -1;
        }

        if (grow_buffer(&buffer, &capacity, used + 2U) != 0) {
            free(buffer);
            return -1;
        }

        buffer[used++] = (char)(unsigned char)ch;
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

static int write_all(FILE *stream, const char *buffer, size_t length)
{
    size_t written = 0;

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
    size_t input_len = 0;
    size_t output_len = 0;
    int status;

    status = read_line(stdin, &input, &input_len);
    if (status < 0) {
        return EXIT_FAILURE;
    }

    if (status == 0) {
        return EXIT_SUCCESS;
    }

    if (add_spaces_before_capitals(input, input_len, &output,
                                   &output_len) != 0) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);

    if (write_all(stdout, output, output_len) != 0 ||
        fputc('\n', stdout) == EOF) {
        free(output);
        return EXIT_FAILURE;
    }

    free(output);

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}