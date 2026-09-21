#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define BYTE_VALUES ((size_t)UCHAR_MAX + 1U)

static bool are_isomorphic(const char *first, size_t first_length,
                           const char *second, size_t second_length)
{
    if (first == NULL || second == NULL || first_length != second_length) {
        return false;
    }

    unsigned char mapping[BYTE_VALUES] = {0};
    bool first_mapped[BYTE_VALUES] = {false};
    bool second_mapped[BYTE_VALUES] = {false};

    for (size_t i = 0; i < first_length; ++i) {
        unsigned char first_char = (unsigned char)first[i];
        unsigned char second_char = (unsigned char)second[i];

        if (first_mapped[first_char]) {
            if (mapping[first_char] != second_char) {
                return false;
            }
        } else {
            if (second_mapped[second_char]) {
                return false;
            }

            mapping[first_char] = second_char;
            first_mapped[first_char] = true;
            second_mapped[second_char] = true;
        }
    }

    return true;
}

static int read_line(FILE *stream, char **line, size_t *length)
{
    if (stream == NULL || line == NULL || length == NULL) {
        return -1;
    }

    *line = NULL;
    *length = 0;

    size_t capacity = 128;
    char *buffer = malloc(capacity);

    if (buffer == NULL) {
        return -1;
    }

    size_t used = 0;

    for (;;) {
        int character = fgetc(stream);

        if (character == '\n') {
            break;
        }

        if (character == EOF) {
            if (ferror(stream) || used == 0) {
                free(buffer);
                return -1;
            }
            break;
        }

        if (used == capacity) {
            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return -1;
            }

            size_t new_capacity = capacity * 2;
            char *new_buffer = realloc(buffer, new_capacity);

            if (new_buffer == NULL) {
                free(buffer);
                return -1;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[used++] = (char)(unsigned char)character;
    }

    *line = buffer;
    *length = used;
    return 0;
}

int main(void)
{
    char *first = NULL;
    char *second = NULL;
    size_t first_length = 0;
    size_t second_length = 0;

    if (read_line(stdin, &first, &first_length) != 0 ||
        read_line(stdin, &second, &second_length) != 0) {
        free(first);
        free(second);
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