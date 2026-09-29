#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BYTE_VALUES ((size_t)UCHAR_MAX + 1U)

static bool are_isomorphic(const unsigned char *first, size_t first_length,
                           const unsigned char *second, size_t second_length)
{
    if (first_length != second_length) {
        return false;
    }

    if (first_length != 0U && (first == NULL || second == NULL)) {
        return false;
    }

    unsigned char forward[BYTE_VALUES] = {0};
    unsigned char reverse[BYTE_VALUES] = {0};
    bool forward_set[BYTE_VALUES] = {false};
    bool reverse_set[BYTE_VALUES] = {false};

    for (size_t i = 0U; i < first_length; ++i) {
        size_t first_index = (size_t)first[i];
        size_t second_index = (size_t)second[i];

        if (first_index >= BYTE_VALUES || second_index >= BYTE_VALUES) {
            return false;
        }

        if (forward_set[first_index]) {
            if (forward[first_index] != second[i]) {
                return false;
            }
        } else {
            forward[first_index] = second[i];
            forward_set[first_index] = true;
        }

        if (reverse_set[second_index]) {
            if (reverse[second_index] != first[i]) {
                return false;
            }
        } else {
            reverse[second_index] = first[i];
            reverse_set[second_index] = true;
        }
    }

    return true;
}

static int read_line(FILE *stream, unsigned char **line, size_t *length)
{
    if (stream == NULL || line == NULL || length == NULL) {
        return -1;
    }

    *line = NULL;
    *length = 0U;

    size_t capacity = 128U;
    size_t used = 0U;
    unsigned char *buffer = malloc(capacity);

    if (buffer == NULL) {
        return -1;
    }

    for (;;) {
        int character = fgetc(stream);

        if (character == '\n') {
            break;
        }

        if (character == EOF) {
            if (ferror(stream) || used == 0U) {
                free(buffer);
                return -1;
            }
            break;
        }

        if (used >= capacity) {
            if (capacity > SIZE_MAX / 2U) {
                free(buffer);
                return -1;
            }

            size_t new_capacity = capacity * 2U;
            unsigned char *new_buffer = realloc(buffer, new_capacity);

            if (new_buffer == NULL) {
                free(buffer);
                return -1;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[used] = (unsigned char)character;
        ++used;
    }

    *line = buffer;
    *length = used;
    return 0;
}

int main(void)
{
    unsigned char *first = NULL;
    unsigned char *second = NULL;
    size_t first_length = 0U;
    size_t second_length = 0U;

    if (read_line(stdin, &first, &first_length) != 0) {
        return EXIT_FAILURE;
    }

    if (read_line(stdin, &second, &second_length) != 0) {
        free(first);
        return EXIT_FAILURE;
    }

    bool result = are_isomorphic(first, first_length,
                                 second, second_length);

    free(first);
    free(second);

    if (puts(result ? "Isomorphic" : "Not isomorphic") == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}