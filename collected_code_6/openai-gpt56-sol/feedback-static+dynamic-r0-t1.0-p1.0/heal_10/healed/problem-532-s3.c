#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>

static bool are_permutations(const char *first, size_t first_length,
                             const char *second, size_t second_length)
{
    if (first == NULL || second == NULL || first_length != second_length) {
        return false;
    }

    size_t frequencies[UCHAR_MAX + 1] = {0};

    for (size_t i = 0; i < first_length; ++i) {
        unsigned char character = (unsigned char)first[i];

        if (frequencies[character] == SIZE_MAX) {
            return false;
        }

        ++frequencies[character];
    }

    for (size_t i = 0; i < second_length; ++i) {
        unsigned char character = (unsigned char)second[i];

        if (frequencies[character] == 0) {
            return false;
        }

        --frequencies[character];
    }

    return true;
}

static bool read_line(FILE *stream, char **line, size_t *length)
{
    if (stream == NULL || line == NULL || length == NULL) {
        return false;
    }

    *line = NULL;
    *length = 0;

    size_t capacity = 128;
    char *buffer = malloc(capacity);

    if (buffer == NULL) {
        return false;
    }

    for (;;) {
        int character = fgetc(stream);

        if (character == EOF) {
            if (ferror(stream) || *length == 0) {
                free(buffer);
                return false;
            }
            break;
        }

        if (character == '\n') {
            break;
        }

        if (*length >= capacity) {
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

        buffer[*length] = (char)(unsigned char)character;
        ++*length;
    }

    *line = buffer;
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

    bool result = are_permutations(first, first_length,
                                   second, second_length);

    free(first);
    free(second);

    if (printf("%s\n", result ? "true" : "false") < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}