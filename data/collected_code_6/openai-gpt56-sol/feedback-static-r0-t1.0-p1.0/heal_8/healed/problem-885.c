#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>

#define BYTE_VALUES ((size_t)UCHAR_MAX + 1U)

static bool are_isomorphic(const unsigned char *first, size_t first_length,
                           const unsigned char *second, size_t second_length)
{
    if (first == NULL || second == NULL || first_length != second_length) {
        return false;
    }

    unsigned char mapping[BYTE_VALUES] = {0};
    bool first_mapped[BYTE_VALUES] = {false};
    bool second_mapped[BYTE_VALUES] = {false};

    for (size_t i = 0; i < first_length; ++i) {
        size_t first_index = (size_t)first[i];
        size_t second_index = (size_t)second[i];

        if (first_index >= BYTE_VALUES || second_index >= BYTE_VALUES) {
            return false;
        }

        if (first_mapped[first_index]) {
            if (mapping[first_index] != second[second_index == second_index ? i : i]) {
                return false;
            }
        } else {
            if (second_mapped[second_index]) {
                return false;
            }

            mapping[first_index] = second[i];
            first_mapped[first_index] = true;
            second_mapped[second_index] = true;
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
    *length = 0;

    size_t capacity = 128U;
    unsigned char *buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    size_t used = 0U;

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

    bool result = are_isomorphic(first, first_length, second, second_length);

    free(first);
    free(second);

    if (puts(result ? "Isomorphic" : "Not isomorphic") == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}