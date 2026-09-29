#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int is_space(unsigned char character)
{
    return character == ' ' || character == '\t' ||
           character == '\n' || character == '\r' ||
           character == '\f' || character == '\v';
}

static void reverse_range(char *start, char *end)
{
    while (start < end) {
        char temporary = *start;
        *start++ = *end;
        *end-- = temporary;
    }
}

static void reverse_words(char *string, size_t length)
{
    char *cursor;
    char *end;

    if (string == NULL || length < 2U) {
        return;
    }

    reverse_range(string, string + length - 1U);

    cursor = string;
    end = string + length;

    while (cursor < end) {
        char *word_start;

        while (cursor < end && is_space((unsigned char)*cursor)) {
            ++cursor;
        }

        word_start = cursor;

        while (cursor < end && !is_space((unsigned char)*cursor)) {
            ++cursor;
        }

        if (word_start < cursor) {
            reverse_range(word_start, cursor - 1);
        }
    }
}

static int grow_buffer(char **buffer, size_t *capacity, size_t required)
{
    size_t new_capacity;
    char *new_buffer;

    if (buffer == NULL || capacity == NULL || *buffer == NULL ||
        *capacity == 0U) {
        return 0;
    }

    if (required <= *capacity) {
        return 1;
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
        return 0;
    }

    new_buffer = realloc(*buffer, new_capacity);
    if (new_buffer == NULL) {
        return 0;
    }

    *buffer = new_buffer;
    *capacity = new_capacity;
    return 1;
}

static int read_line(FILE *stream, char **line, size_t *length)
{
    size_t capacity = 128U;
    size_t used = 0U;
    char *buffer;
    int character;

    if (stream == NULL || line == NULL || length == NULL) {
        return 0;
    }

    *line = NULL;
    *length = 0U;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stream)) != EOF && character != '\n') {
        if (used >= SIZE_MAX - 1U) {
            free(buffer);
            return 0;
        }

        if (!grow_buffer(&buffer, &capacity, used + 2U)) {
            free(buffer);
            return 0;
        }

        buffer[used++] = (char)(unsigned char)character;
    }

    if (character == EOF && ferror(stream)) {
        free(buffer);
        return 0;
    }

    if (!grow_buffer(&buffer, &capacity, used + 1U)) {
        free(buffer);
        return 0;
    }

    buffer[used] = '\0';
    *line = buffer;
    *length = used;
    return 1;
}

int main(void)
{
    char *line = NULL;
    size_t length = 0U;
    int status = EXIT_SUCCESS;

    if (!read_line(stdin, &line, &length)) {
        return EXIT_FAILURE;
    }

    reverse_words(line, length);

    if (fwrite(line, sizeof(*line), length, stdout) != length ||
        fputc('\n', stdout) == EOF) {
        status = EXIT_FAILURE;
    }

    free(line);
    return status;
}