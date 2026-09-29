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

static int grow_buffer(char **buffer, size_t *capacity, size_t required)
{
    size_t new_capacity;
    char *new_buffer;

    if (buffer == NULL || *buffer == NULL || capacity == NULL ||
        *capacity == 0U) {
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

    if (new_capacity < required) {
        return -1;
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
    const size_t initial_capacity = 128U;
    size_t capacity = initial_capacity;
    size_t used = 0U;
    char *buffer;
    int character;

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
        character = fgetc(stream);

        if (character == EOF || character == '\n') {
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

        buffer[used] = (char)(unsigned char)character;
        ++used;
    }

    if (character == EOF && (ferror(stream) != 0 || used == 0U)) {
        free(buffer);
        return -1;
    }

    if (used == SIZE_MAX ||
        grow_buffer(&buffer, &capacity, used + 1U) != 0) {
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