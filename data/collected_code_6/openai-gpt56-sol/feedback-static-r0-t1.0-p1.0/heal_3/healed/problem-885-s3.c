#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

static bool read_line(FILE *stream, char **line, size_t *length)
{
    size_t capacity = 128;
    size_t used = 0;
    char *buffer;

    if (stream == NULL || line == NULL || length == NULL) {
        return false;
    }

    *line = NULL;
    *length = 0;

    buffer = malloc(capacity);
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

        if (ch == '\r') {
            int next = fgetc(stream);

            if (next == EOF) {
                if (ferror(stream)) {
                    free(buffer);
                    return false;
                }
            } else if (next != '\n' && ungetc(next, stream) == EOF) {
                free(buffer);
                return false;
            }

            break;
        }

        if (used == capacity - 1) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return false;
            }

            new_capacity = capacity * 2;
            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return false;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[used++] = (char)(unsigned char)ch;
    }

    buffer[used] = '\0';
    *line = buffer;
    *length = used;

    return true;
}

static bool are_isomorphic(const char *first, size_t first_length,
                           const char *second, size_t second_length)
{
    int first_to_second[UCHAR_MAX + 1];
    int second_to_first[UCHAR_MAX + 1];
    size_t i;

    if (first == NULL || second == NULL || first_length != second_length) {
        return false;
    }

    for (i = 0; i <= UCHAR_MAX; ++i) {
        first_to_second[i] = -1;
        second_to_first[i] = -1;
    }

    for (i = 0; i < first_length; ++i) {
        unsigned char first_char = (unsigned char)first[i];
        unsigned char second_char = (unsigned char)second[i];

        if (first_to_second[first_char] == -1 &&
            second_to_first[second_char] == -1) {
            first_to_second[first_char] = second_char;
            second_to_first[second_char] = first_char;
        } else if (first_to_second[first_char] != second_char ||
                   second_to_first[second_char] != first_char) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    char *first = NULL;
    char *second = NULL;
    size_t first_length = 0;
    size_t second_length = 0;
    bool result;

    if (!read_line(stdin, &first, &first_length) ||
        !read_line(stdin, &second, &second_length)) {
        free(first);
        free(second);
        return EXIT_FAILURE;
    }

    result = are_isomorphic(first, first_length, second, second_length);
    puts(result ? "Isomorphic" : "Not isomorphic");

    free(first);
    free(second);

    return EXIT_SUCCESS;
}