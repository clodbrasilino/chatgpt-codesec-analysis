#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool are_isomorphic(const char *first, size_t first_length,
                           const char *second, size_t second_length)
{
    if (first == NULL || second == NULL || first_length != second_length) {
        return false;
    }

    unsigned int first_to_second[UCHAR_MAX + 1U] = {0};
    bool first_mapped[UCHAR_MAX + 1U] = {false};
    bool second_mapped[UCHAR_MAX + 1U] = {false};

    for (size_t i = 0; i < first_length; ++i) {
        unsigned char first_char = (unsigned char)first[i];
        unsigned char second_char = (unsigned char)second[i];

        if (first_mapped[first_char]) {
            if (first_to_second[first_char] != second_char) {
                return false;
            }
        } else {
            if (second_mapped[second_char]) {
                return false;
            }

            first_to_second[first_char] = second_char;
            first_mapped[first_char] = true;
            second_mapped[second_char] = true;
        }
    }

    return true;
}

static bool read_line(FILE *stream, char **line, size_t *length)
{
    if (stream == NULL || line == NULL || length == NULL) {
        return false;
    }

    size_t capacity = 128;
    size_t used = 0;
    char *buffer = malloc(capacity);

    if (buffer == NULL) {
        return false;
    }

    for (;;) {
        int ch = fgetc(stream);

        if (ch == EOF) {
            if (ferror(stream) || used == 0) {
                free(buffer);
                return false;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (used == SIZE_MAX - 1) {
            free(buffer);
            return false;
        }

        if (used + 1 >= capacity) {
            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return false;
            }

            size_t new_capacity = capacity * 2;
            char *new_buffer = realloc(buffer, new_capacity);

            if (new_buffer == NULL) {
                free(buffer);
                return false;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[used++] = (char)ch;
    }

    if (used > 0 && buffer[used - 1] == '\r') {
        --used;
    }

    buffer[used] = '\0';
    *line = buffer;
    *length = used;
    return true;
}

int main(void)
{
    char *first = NULL;
    char *second = NULL;
    size_t first_length = 0;
    size_t second_length = 0;

    if (!read_line(stdin, &first, &first_length) ||
        !read_line(stdin, &second, &second_length)) {
        free(first);
        free(second);
        return EXIT_FAILURE;
    }

    bool result = are_isomorphic(first, first_length, second, second_length);

    free(first);
    free(second);

    if (puts(result ? "Isomorphic" : "Not isomorphic") == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}