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

static int read_line(FILE *stream, char **line, size_t *line_length)
{
    char *buffer = NULL;
    size_t capacity = 0;
    size_t length = 0;

    if (stream == NULL || line == NULL || line_length == NULL) {
        return -1;
    }

    *line = NULL;
    *line_length = 0;

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

            if (length == 0) {
                free(buffer);
                return 0;
            }

            break;
        }

        if (ch == '\n') {
            break;
        }

        if (length > SIZE_MAX - 2) {
            free(buffer);
            return -1;
        }

        if (capacity < length + 2) {
            size_t required = length + 2;
            size_t new_capacity = capacity == 0 ? 128 : capacity;
            char *resized;

            while (new_capacity < required) {
                if (new_capacity > SIZE_MAX / 2) {
                    new_capacity = required;
                    break;
                }
                new_capacity *= 2;
            }

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

    if (buffer == NULL) {
        buffer = malloc(1);
        if (buffer == NULL) {
            return -1;
        }
        /* Possible weaknesses found:
         *  Value stored to 'capacity' is never read [deadcode.DeadStores]
         *  Variable 'capacity' is assigned a value that is never used. [unreadVariable]
         */
        capacity = 1;
    }

    if (length > 0 && buffer[length - 1] == '\r') {
        --length;
    }

    buffer[length] = '\0';
    *line = buffer;
    *line_length = length;
    return 1;
}

int main(void)
{
    char *input = NULL;
    char *output = NULL;
    size_t input_length = 0;
    int read_status = read_line(stdin, &input, &input_length);

    if (read_status < 0) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (read_status == 0) {
        return EXIT_SUCCESS;
    }

    if (remove_lowercase_substrings(input, input_length, &output) != 0) {
        free(input);
        fputs("Failed to process input.\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    if (fputs(output, stdout) == EOF || fputc('\n', stdout) == EOF) {
        free(output);
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    free(output);
    return EXIT_SUCCESS;
}