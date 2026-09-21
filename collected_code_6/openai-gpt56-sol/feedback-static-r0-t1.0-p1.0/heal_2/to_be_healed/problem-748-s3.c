#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int add_spaces_before_capitals(const char *input, size_t input_len,
                                      char **output)
{
    size_t extra_spaces = 0;
    size_t output_len;
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
            ++extra_spaces;
        }
    }

    if (input_len > SIZE_MAX - extra_spaces - 1U) {
        return -1;
    }

    output_len = input_len + extra_spaces;
    result = malloc(output_len + 1U);
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

static int read_line(FILE *stream, char **line, size_t *length)
{
    size_t capacity = 128U;
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
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stream);

        if (ch == EOF) {
            if (ferror(stream)) {
                free(buffer);
                return -1;
            }

            if (used == 0U) {
                free(buffer);
                return 0;
            }

            break;
        }

        if (ch == '\n') {
            break;
        }

        if (used == capacity - 1U) {
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

        buffer[used++] = (char)ch;
    }

    buffer[used] = '\0';
    *line = buffer;
    *length = used;
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
        return EXIT_FAILURE;
    }

    if (status == 0) {
        return EXIT_SUCCESS;
    }

    if (add_spaces_before_capitals(input, input_len, &output) != 0) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    if (fwrite(output, 1U, strlen(output), stdout) != strlen(output) ||
        fputc('\n', stdout) == EOF) {
        free(output);
        return EXIT_FAILURE;
    }

    free(output);
    return EXIT_SUCCESS;
}