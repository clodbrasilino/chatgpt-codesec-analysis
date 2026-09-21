#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool all_characters_unique(const char *str)
{
    bool seen[256] = { false };

    if (str == NULL) {
        return false;
    }

    while (*str != '\0') {
        unsigned char character = (unsigned char)*str;

        if (seen[character]) {
            return false;
        }

        seen[character] = true;
        ++str;
    }

    return true;
}

static int read_line(FILE *stream, char **result)
{
    char *buffer;
    size_t length;
    size_t capacity;
    int ch;

    if (stream == NULL || result == NULL) {
        return -1;
    }

    *result = NULL;
    capacity = 128;
    length = 0;
    buffer = malloc(capacity);

    if (buffer == NULL) {
        return -1;
    }

    for (;;) {
        ch = fgetc(stream);

        if (ch == EOF || ch == '\n') {
            break;
        }

        if (length == capacity - 1) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return -1;
            }

            new_capacity = capacity * 2;
            new_buffer = realloc(buffer, new_capacity);

            if (new_buffer == NULL) {
                free(buffer);
                return -1;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)(unsigned char)ch;
    }

    if (ferror(stream)) {
        free(buffer);
        return -1;
    }

    buffer[length] = '\0';
    *result = buffer;
    return 0;
}

int main(void)
{
    char *input = NULL;

    if (read_line(stdin, &input) != 0) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    puts(all_characters_unique(input) ? "true" : "false");

    free(input);
    return EXIT_SUCCESS;
}