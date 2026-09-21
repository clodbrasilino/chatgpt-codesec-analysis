#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

static bool read_line(FILE *stream, char **line, size_t *length)
{
    char *buffer = NULL;
    size_t used = 0;
    size_t capacity = 0;
    int ch = EOF;

    if (stream == NULL || line == NULL || length == NULL) {
        return false;
    }

    *line = NULL;
    *length = 0;

    while ((ch = fgetc(stream)) != EOF) {
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
            }
            break;
        }

        if (used == capacity) {
            size_t new_capacity;
            char *temporary;

            if (capacity == 0) {
                new_capacity = 128;
            } else {
                if (capacity > (SIZE_MAX - 1) / 2) {
                    free(buffer);
                    return false;
                }
                new_capacity = capacity * 2;
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

    if (ferror(stream) || (ch == EOF && used == 0)) {
        free(buffer);
        return false;
    }

    if (used == SIZE_MAX) {
        free(buffer);
        return false;
    }

    if (capacity < used + 1) {
        char *temporary = realloc(buffer, used + 1);

        if (temporary == NULL) {
            free(buffer);
            return false;
        }

        buffer = temporary;
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

    doubled = malloc((first_length * 2) + 1);
    if (doubled == NULL) {
        return false;
    }

    memcpy(doubled, first, first_length);
    memcpy(doubled + first_length, first, first_length);
    doubled[first_length * 2] = '\0';

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

    puts(result ? "Yes" : "No");
    return EXIT_SUCCESS;
}