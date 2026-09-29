#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

static bool read_line(FILE *stream, char **line, size_t *length)
{
    size_t used = 0;
    size_t capacity = 128;
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
            } else if (next != '\n') {
                if (ungetc(next, stream) == EOF) {
                    free(buffer);
                    return false;
                }
            }

            break;
        }

        if (used == SIZE_MAX - 1) {
            free(buffer);
            return false;
        }

        if (used + 1 >= capacity) {
            size_t required = used + 2;
            size_t new_capacity;
            char *temporary;

            if (capacity > SIZE_MAX / 2) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2;
            }

            if (new_capacity < required) {
                new_capacity = required;
            }

            if (new_capacity <= capacity) {
                free(buffer);
                return false;
            }

            temporary = realloc(buffer, new_capacity);
            if (temporary == NULL) {
                free(buffer);
                return false;
            }

            buffer = temporary;
            capacity = new_capacity;
        }

        buffer[used] = (char)(unsigned char)ch;
        ++used;
    }

    buffer[used] = '\0';
    *line = buffer;
    *length = used;
    return true;
}

static bool matches_rotation(const char *first, const char *second,
                             size_t length, size_t offset)
{
    size_t first_part;

    if (first == NULL || second == NULL || offset >= length) {
        return false;
    }

    first_part = length - offset;

    for (size_t i = 0; i < first_part; ++i) {
        if (second[i] != first[offset + i]) {
            return false;
        }
    }

    for (size_t i = 0; i < offset; ++i) {
        if (second[first_part + i] != first[i]) {
            return false;
        }
    }

    return true;
}

static bool are_rotations(const char *first, size_t first_length,
                          const char *second, size_t second_length)
{
    if (first == NULL || second == NULL || first_length != second_length) {
        return false;
    }

    if (first_length == 0) {
        return true;
    }

    for (size_t offset = 0; offset < first_length; ++offset) {
        if (first[offset] == second[0] &&
            matches_rotation(first, second, first_length, offset)) {
            return true;
        }
    }

    return false;
}

int main(void)
{
    char *first = NULL;
    char *second = NULL;
    size_t first_length = 0;
    size_t second_length = 0;
    bool result;

    if (!read_line(stdin, &first, &first_length)) {
        return EXIT_FAILURE;
    }

    if (!read_line(stdin, &second, &second_length)) {
        free(first);
        return EXIT_FAILURE;
    }

    result = are_rotations(first, first_length, second, second_length);

    free(second);
    free(first);

    if (puts(result ? "Yes" : "No") == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}