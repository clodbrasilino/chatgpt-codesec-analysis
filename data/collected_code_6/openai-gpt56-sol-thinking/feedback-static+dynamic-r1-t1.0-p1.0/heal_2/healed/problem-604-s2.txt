#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static void reverse_range(char *buffer, size_t first, size_t last)
{
    while (first < last) {
        char temporary;

        --last;
        if (first >= last) {
            break;
        }

        temporary = buffer[first];
        buffer[first] = buffer[last];
        buffer[last] = temporary;
        ++first;
    }
}

static bool reverse_words(char *buffer, size_t buffer_size,
                          size_t length, size_t *result_length)
{
    size_t position = 0U;
    size_t read_position = 0U;
    size_t write_position = 0U;

    if (buffer == NULL || result_length == NULL ||
        buffer_size == 0U || length >= buffer_size) {
        return false;
    }

    reverse_range(buffer, 0U, length);

    while (position < length) {
        size_t word_start;

        while (position < length &&
               isspace((unsigned char)buffer[position]) != 0) {
            ++position;
        }

        word_start = position;

        while (position < length &&
               isspace((unsigned char)buffer[position]) == 0) {
            ++position;
        }

        reverse_range(buffer, word_start, position);
    }

    while (read_position < length) {
        while (read_position < length &&
               isspace((unsigned char)buffer[read_position]) != 0) {
            ++read_position;
        }

        if (read_position == length) {
            break;
        }

        if (write_position != 0U) {
            buffer[write_position++] = ' ';
        }

        while (read_position < length &&
               isspace((unsigned char)buffer[read_position]) == 0) {
            buffer[write_position++] = buffer[read_position++];
        }
    }

    buffer[write_position] = '\0';
    *result_length = write_position;
    return true;
}

static bool read_line(FILE *stream, char **buffer_out,
                      size_t *length_out, size_t *capacity_out)
{
    size_t capacity = 128U;
    size_t length = 0U;
    char *buffer;

    if (stream == NULL || buffer_out == NULL ||
        length_out == NULL || capacity_out == NULL) {
        return false;
    }

    *buffer_out = NULL;
    *length_out = 0U;
    *capacity_out = 0U;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return false;
    }

    for (;;) {
        size_t count;

        if (length >= capacity - 1U) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2U) {
                free(buffer);
                return false;
            }

            new_capacity = capacity * 2U;
            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return false;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        count = fread(buffer + length, 1U, 1U, stream);

        if (count == 0U) {
            if (ferror(stream) != 0 || feof(stream) == 0) {
                free(buffer);
                return false;
            }
            break;
        }

        if (buffer[length] == '\n') {
            break;
        }

        ++length;
    }

    if (length > 0U && buffer[length - 1U] == '\r') {
        --length;
    }

    buffer[length] = '\0';

    *buffer_out = buffer;
    *length_out = length;
    *capacity_out = capacity;
    return true;
}

int main(void)
{
    char *buffer;
    size_t length;
    size_t capacity;
    size_t result_length;
    int result = EXIT_SUCCESS;

    if (!read_line(stdin, &buffer, &length, &capacity)) {
        return EXIT_FAILURE;
    }

    if (!reverse_words(buffer, capacity, length, &result_length)) {
        free(buffer);
        return EXIT_FAILURE;
    }

    if ((result_length > 0U &&
         fwrite(buffer, 1U, result_length, stdout) != result_length) ||
        fputc('\n', stdout) == EOF) {
        result = EXIT_FAILURE;
    }

    free(buffer);
    return result;
}