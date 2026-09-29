#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static bool read_line(FILE *stream, char **line, size_t *length)
{
    char *buffer;
    size_t capacity = 128;
    size_t used = 0;

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
        int character = fgetc(stream);

        if (character == EOF) {
            if (ferror(stream) || used == 0) {
                free(buffer);
                return false;
            }
            break;
        }

        if (character == '\n') {
            break;
        }

        if (used > SIZE_MAX - 2) {
            free(buffer);
            return false;
        }

        if (used + 1 >= capacity) {
            size_t required = used + 2;
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2;
            }

            if (new_capacity < required) {
                free(buffer);
                return false;
            }

            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return false;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[used++] = (char)(unsigned char)character;
    }

    buffer[used] = '\0';
    *line = buffer;
    *length = used;
    return true;
}

static bool are_permutations(const char *first, size_t first_length,
                             const char *second, size_t second_length)
{
    size_t frequencies[UCHAR_MAX + 1] = {0};

    if (first == NULL || second == NULL || first_length != second_length) {
        return false;
    }

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

    if (puts(are_permutations(first, first_length, second, second_length)
                 ? "The strings are permutations of each other."
                 : "The strings are not permutations of each other.") == EOF) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(second);
    free(first);
    return status;
}