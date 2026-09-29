#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static bool are_permutations(const char *first, const char *second)
{
    size_t frequencies[UCHAR_MAX + 1] = {0};

    if (first == NULL || second == NULL) {
        return false;
    }

    while (*first != '\0') {
        unsigned char character = (unsigned char)*first++;

        if (frequencies[character] == SIZE_MAX) {
            return false;
        }

        ++frequencies[character];
    }

    while (*second != '\0') {
        unsigned char character = (unsigned char)*second++;

        if (frequencies[character] == 0) {
            return false;
        }

        --frequencies[character];
    }

    for (size_t i = 0; i <= UCHAR_MAX; ++i) {
        if (frequencies[i] != 0) {
            return false;
        }
    }

    return true;
}

static char *read_line(FILE *stream)
{
    size_t length = 0;
    size_t capacity = 128;
    char *buffer;
    int character = EOF;

    if (stream == NULL) {
        return NULL;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return NULL;
    }

    for (;;) {
        character = fgetc(stream);

        if (character == EOF || character == '\n') {
            break;
        }

        if (length >= capacity - 1) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return NULL;
            }

            new_capacity = capacity * 2;
            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return NULL;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)(unsigned char)character;
    }

    if (ferror(stream) || (character == EOF && length == 0)) {
        free(buffer);
        return NULL;
    }

    buffer[length] = '\0';
    return buffer;
}

int main(void)
{
    char *first;
    char *second;
    int result;

    first = read_line(stdin);
    if (first == NULL) {
        return EXIT_FAILURE;
    }

    second = read_line(stdin);
    if (second == NULL) {
        free(first);
        return EXIT_FAILURE;
    }

    result = printf("%s\n",
                    are_permutations(first, second) ? "true" : "false");

    free(second);
    free(first);

    return result < 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}