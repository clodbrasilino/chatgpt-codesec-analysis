#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int add_spaces_before_capitals(const char *input, char **output)
{
    size_t input_len;
    size_t extra = 0;
    size_t capacity;
    size_t read_pos;
    size_t write_pos = 0;
    char *result;

    if (input == NULL || output == NULL) {
        return -1;
    }

    *output = NULL;
    input_len = strlen(input);

    for (read_pos = 0; read_pos < input_len; ++read_pos) {
        if (isupper((unsigned char)input[read_pos]) &&
            read_pos > 0 &&
            input[read_pos - 1] != ' ') {
            ++extra;
        }
    }

    if (input_len > SIZE_MAX - extra - 1U) {
        return -1;
    }

    capacity = input_len + extra + 1U;
    result = malloc(capacity);
    if (result == NULL) {
        return -1;
    }

    for (read_pos = 0; read_pos < input_len; ++read_pos) {
        if (isupper((unsigned char)input[read_pos]) &&
            read_pos > 0 &&
            input[read_pos - 1] != ' ') {
            result[write_pos++] = ' ';
        }

        result[write_pos++] = input[read_pos];
    }

    result[write_pos] = '\0';
    *output = result;
    return 0;
}

static int read_line(char **line)
{
    size_t capacity = 128U;
    size_t length = 0;
    char *buffer;
    int ch;

    if (line == NULL) {
        return -1;
    }

    *line = NULL;
    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
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

        buffer[length++] = (char)ch;
    }

    if (ch == EOF && ferror(stdin)) {
        free(buffer);
        return -1;
    }

    if (ch == EOF && length == 0U) {
        free(buffer);
        return 1;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 0;
}

int main(void)
{
    char *input = NULL;
    char *output = NULL;
    int status;

    status = read_line(&input);
    if (status != 0) {
        return EXIT_FAILURE;
    }

    if (add_spaces_before_capitals(input, &output) != 0) {
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