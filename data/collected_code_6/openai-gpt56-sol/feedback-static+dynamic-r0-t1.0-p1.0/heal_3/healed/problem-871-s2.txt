#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

static bool read_line(FILE *stream, char **line, size_t *length)
{
    char *buffer;
    size_t used = 0;
    size_t capacity = 128;
    int ch;

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
        ch = fgetc(stream);

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

            if (next != '\n' && next != EOF) {
                if (ungetc(next, stream) == EOF) {
                    free(buffer);
                    return false;
                }
            } else if (next == EOF && ferror(stream)) {
                free(buffer);
                return false;
            }

            break;
        }

        if (used == SIZE_MAX - 1) {
            free(buffer);
            return false;
        }

        if (used + 1 >= capacity) {
            size_t new_capacity;
            char *temporary;

            if (capacity > SIZE_MAX / 2) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2;
            }

            if (new_capacity <= capacity || new_capacity <= used) {
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

        buffer[used++] = (char)ch;
    }

    buffer[used] = '\0';
    *line = buffer;
    *length = used;
    return true;
}

static bool are_rotations(const char *first, size_t first_length,
                          const char *second, size_t second_length)
{
    char *doubled;
    size_t doubled_length;
    bool result;

    if (first == NULL || second == NULL || first_length != second_length) {
        return false;
    }

    if (first_length == 0) {
        return true;
    }

    if (first_length > (SIZE_MAX - 1) / 2) {
        return false;
    }

    doubled_length = first_length * 2;
    doubled = malloc(doubled_length + 1);
    if (doubled == NULL) {
        return false;
    }

    memcpy(doubled, first, first_length);
    memcpy(doubled + first_length, first, first_length);
    doubled[doubled_length] = '\0';

    result = strstr(doubled, second) != NULL;

    free(doubled);
    return result;
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

    free(first);
    free(second);

    if (puts(result ? "Yes" : "No") == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}