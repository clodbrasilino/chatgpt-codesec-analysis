#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool are_permutations(const char *first, size_t first_length,
                             const char *second, size_t second_length)
{
    size_t frequencies[256] = {0};

    if (first == NULL || second == NULL || first_length != second_length) {
        return false;
    }

    for (size_t i = 0; i < first_length; ++i) {
        ++frequencies[(unsigned char)first[i]];
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

static bool read_line(char **line, size_t *length)
{
    size_t capacity = 128;
    char *buffer = malloc(capacity);

    if (line == NULL || length == NULL || buffer == NULL) {
        free(buffer);
        return false;
    }

    *length = 0;

    for (;;) {
        int character = fgetc(stdin);

        if (character == '\n' || character == EOF) {
            if (character == EOF && ferror(stdin)) {
                free(buffer);
                return false;
            }

            if (character == EOF && *length == 0) {
                free(buffer);
                return false;
            }

            break;
        }

        if (*length == capacity) {
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

        buffer[(*length)++] = (char)character;
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

    if (!read_line(&first, &first_length) ||
        !read_line(&second, &second_length)) {
        free(first);
        free(second);
        return 1;
    }

    bool result = are_permutations(first, first_length,
                                   second, second_length);

    free(first);
    free(second);

    if (printf("%s\n", result ? "true" : "false") < 0) {
        return 1;
    }

    return 0;
}