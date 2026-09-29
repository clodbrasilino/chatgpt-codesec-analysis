#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>

static int count_nonempty_substrings(size_t length, uintmax_t *count)
{
    uintmax_t n;

    if (count == NULL) {
        return 0;
    }

    n = (uintmax_t)length;

    if ((size_t)n != length || (n != 0 && n > UINTMAX_MAX / (n + 1))) {
        return 0;
    }

    *count = n * (n + 1) / 2;
    return 1;
}

static int read_line(FILE *stream, char **line, size_t *length)
{
    char *buffer;
    size_t capacity = 128;
    size_t used = 0;
    int ch;

    if (stream == NULL || line == NULL || length == NULL) {
        return 0;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return 0;
    }

    while ((ch = fgetc(stream)) != '\n' && ch != EOF) {
        if (used == capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return 0;
            }

            new_capacity = capacity * 2;
            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return 0;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[used++] = (char)ch;
    }

    if (ch == EOF && (ferror(stream) || used == 0)) {
        free(buffer);
        return 0;
    }

    *line = buffer;
    *length = used;
    return 1;
}

int main(void)
{
    char *input;
    size_t length;
    uintmax_t count;

    if (!read_line(stdin, &input, &length)) {
        return EXIT_FAILURE;
    }

    if (!count_nonempty_substrings(length, &count)) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);

    if (printf("%" PRIuMAX "\n", count) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}