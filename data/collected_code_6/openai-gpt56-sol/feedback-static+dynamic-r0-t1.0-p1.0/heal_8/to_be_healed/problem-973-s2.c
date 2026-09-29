#include <errno.h>
#include <inttypes.h>
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

static int grow_buffer(char **buffer, size_t *capacity)
{
    char *temporary;
    size_t new_capacity;

    if (buffer == NULL || *buffer == NULL || capacity == NULL ||
        *capacity == 0U) {
        return -1;
    }

    if (*capacity > SIZE_MAX / 2U) {
        return -1;
    }

    new_capacity = *capacity * 2U;
    temporary = realloc(*buffer, new_capacity);

    if (temporary == NULL) {
        return -1;
    }

    *buffer = temporary;
    *capacity = new_capacity;

    return 0;
}

static int read_line(FILE *stream, char **line, size_t *length)
{
    char *buffer;
    size_t capacity = 128U;
    size_t used = 0U;

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

        if (character == '\n') {
            break;
        }

        if (used >= capacity - 1U) {
            if (grow_buffer(&buffer, &capacity) != 0) {
                free(buffer);
                return -1;
            }
        }

        buffer[used++] = (char)(unsigned char)character;
    }

    buffer[used] = '\0';
    *line = buffer;
    *length = used;

    return 1;
}

static int is_space_character(char character)
{
    return character == ' ' || character == '\t' || character == '\r' ||
           character == '\n' || character == '\v' || character == '\f';
}

int main(void)
{
    char *input = NULL;
    char *rotation_text = NULL;
    char *end = NULL;
    size_t input_length = 0U;
    size_t rotation_text_length = 0U;
    size_t rotation;
    uintmax_t parsed_rotation;
    int status;
    int result = EXIT_FAILURE;

    status = read_line(stdin, &input, &input_length);
    if (status != 1) {
        goto cleanup;
    }

    status = read_line(stdin, &rotation_text, &rotation_text_length);
    if (status != 1) {
        goto cleanup;
    }

    errno = 0;
    parsed_rotation = strtoumax(rotation_text, &end, 10);

    if (end == rotation_text || errno == ERANGE) {
        goto cleanup;
    }

    while (*end != '\0' && is_space_character(*end)) {
        ++end;
    }

    if (*end != '\0' || parsed_rotation > (uintmax_t)SIZE_MAX) {
        goto cleanup;
    }

    rotation = (size_t)parsed_rotation;

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