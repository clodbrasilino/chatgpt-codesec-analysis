#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static void reverse_range(char *string, size_t begin, size_t end)
{
    while (begin < end) {
        char temporary = string[begin];
        string[begin++] = string[end];
        string[end--] = temporary;
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

static int read_line(char **line, size_t *length)
{
    size_t capacity = 128U;
    size_t used = 0U;
    char *buffer;
    int character;

    if (line == NULL || length == NULL) {
        return -1;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    while ((character = fgetc(stdin)) != '\n' && character != EOF) {
        if (used == SIZE_MAX - 1U) {
            free(buffer);
            return -1;
        }

        if (used + 1U >= capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2U) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2U;
            }

            if (new_capacity <= used + 1U) {
                free(buffer);
                return -1;
            }

            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return -1;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[used++] = (char)character;
    }

    if (character == EOF && (ferror(stdin) || used == 0U)) {
        free(buffer);
        return -1;
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

    if (text == NULL || rotation == NULL) {
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
    size_t input_length;
    size_t rotation_text_length;
    size_t rotation;
    int result = EXIT_FAILURE;

    if (read_line(&input, &input_length) != 0) {
        goto cleanup;
    }

    if (read_line(&rotation_text, &rotation_text_length) != 0) {
        goto cleanup;
    }

    (void)rotation_text_length;

    if (parse_rotation(rotation_text, &rotation) != 0) {
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