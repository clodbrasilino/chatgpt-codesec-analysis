#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static bool read_line(char **line, size_t *length)
{
    char *buffer = NULL;
    size_t capacity = 128;
    size_t used = 0;

    if (line == NULL || length == NULL) {
        return false;
    }

    *line = NULL;
    *length = 0;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return false;
    }

    for (;;) {
        int character = fgetc(stdin);

        if (character == '\n') {
            break;
        }

        if (character == EOF) {
            if (ferror(stdin) || used == 0) {
                free(buffer);
                return false;
            }
            break;
        }

        if (used == capacity - 1) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return false;
            }

            new_capacity = capacity * 2;
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
    size_t frequencies[UINT8_MAX + 1] = {0};

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
    int status = EXIT_SUCCESS;

    if (!read_line(&first, &first_length) ||
        !read_line(&second, &second_length)) {
        free(first);
        free(second);
        return EXIT_FAILURE;
    }

    if (puts(are_permutations(first, first_length, second, second_length)
                 ? "The strings are permutations of each other."
                 : "The strings are not permutations of each other.") == EOF) {
        status = EXIT_FAILURE;
    }

    free(first);
    free(second);
    return status;
}