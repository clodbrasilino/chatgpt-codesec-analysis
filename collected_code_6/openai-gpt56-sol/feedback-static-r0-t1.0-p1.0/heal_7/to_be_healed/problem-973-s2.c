#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static void reverse_range(char *string, size_t begin, size_t end)
{
    while (begin < end) {
        char temporary = string[begin];
        string[begin] = string[end];
        string[end] = temporary;
        ++begin;
        --end;
    }
}

static int left_rotate(char *string, size_t length, size_t positions)
{
    if (string == NULL) {
        return -1;
    }

    if (length == 0U) {
        return 0;
    }

    positions %= length;

    if (positions == 0U) {
        return 0;
    }

    reverse_range(string, 0U, positions - 1U);
    reverse_range(string, positions, length - 1U);
    reverse_range(string, 0U, length - 1U);

    return 0;
}

static int read_line(FILE *stream, char **line, size_t *length)
{
    size_t capacity = 128U;
    size_t used = 0U;
    char *buffer;

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
        int character = fgetc(stream);

        if (character == EOF) {
            if (ferror(stream) || used == 0U) {
                free(buffer);
                return -1;
            }
            break;
        }

        if (character == '\n') {
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

        buffer[used++] = (char)(unsigned char)character;
    }

    buffer[used] = '\0';
    *line = buffer;
    *length = used;

    return 0;
}

static int parse_rotation(const char *text, size_t *rotation)
{
    char *end;
    unsigned long long value;

    if (text == NULL || rotation == NULL || text[0] == '\0' ||
        text[0] == '-') {
        return -1;
    }

    errno = 0;
    value = strtoull(text, &end, 10);

    if (end == text || errno == ERANGE) {
        return -1;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\n' || *end == '\v' || *end == '\f') {
        ++end;
    }

    if (*end != '\0' || value > (unsigned long long)SIZE_MAX) {
        return -1;
    }

    *rotation = (size_t)value;
    return 0;
}

int main(void)
{
    char *input = NULL;
    char *rotation_text = NULL;
    size_t input_length = 0U;
    size_t rotation_text_length = 0U;
    size_t rotation;
    int result = EXIT_FAILURE;

    if (read_line(stdin, &input, &input_length) != 0) {
        goto cleanup;
    }

    if (read_line(stdin, &rotation_text, &rotation_text_length) != 0) {
        goto cleanup;
    }

    if (rotation_text_length == 0U ||
        parse_rotation(rotation_text, &rotation) != 0) {
        goto cleanup;
    }

    if (left_rotate(input, input_length, rotation) != 0) {
        goto cleanup;
    }

    if (puts(input) == EOF) {
        goto cleanup;
    }

    result = EXIT_SUCCESS;

cleanup:
    free(rotation_text);
    free(input);
    return result;
}