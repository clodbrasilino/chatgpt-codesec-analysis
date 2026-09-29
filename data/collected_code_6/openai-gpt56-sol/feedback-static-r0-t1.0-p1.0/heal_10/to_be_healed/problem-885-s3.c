#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

static bool grow_buffer(char **buffer, size_t *capacity)
{
    size_t new_capacity;
    char *new_buffer;

    if (buffer == NULL || *buffer == NULL || capacity == NULL ||
        *capacity == 0 || *capacity > SIZE_MAX / 2) {
        return false;
    }

    new_capacity = *capacity * 2;
    new_buffer = realloc(*buffer, new_capacity);
    if (new_buffer == NULL) {
        return false;
    }

    *buffer = new_buffer;
    *capacity = new_capacity;
    return true;
}

static bool append_character(char **buffer, size_t *capacity,
                             size_t *used, unsigned char character)
{
    if (buffer == NULL || capacity == NULL || used == NULL ||
        *buffer == NULL || *capacity == 0 || *used >= *capacity) {
        return false;
    }

    if (*used == SIZE_MAX) {
        return false;
    }

    if (*used + 1 >= *capacity && !grow_buffer(buffer, capacity)) {
        return false;
    }

    (*buffer)[(*used)++] = (char)character;
    return true;
}

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
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
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
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
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

        if (!append_character(&buffer, &capacity, &used,
                              (unsigned char)ch)) {
            free(buffer);
            return false;
        }
    }

    if (used >= capacity) {
        free(buffer);
        return false;
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
            first_to_second[first_char] = (int)second_char;
            second_to_first[second_char] = (int)first_char;
        } else if (first_to_second[first_char] != (int)second_char ||
                   second_to_first[second_char] != (int)first_char) {
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
    int status = EXIT_FAILURE;

    if (!read_line(stdin, &first, &first_length)) {
        goto cleanup;
    }

    if (!read_line(stdin, &second, &second_length)) {
        goto cleanup;
    }

    if (puts(are_isomorphic(first, first_length, second, second_length)
                 ? "Isomorphic"
                 : "Not isomorphic") == EOF) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(second);
    free(first);
    return status;
}