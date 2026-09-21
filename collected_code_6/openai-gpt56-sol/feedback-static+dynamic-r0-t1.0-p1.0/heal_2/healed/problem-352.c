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
    char *buffer = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int ch;

    if (stream == NULL || result == NULL) {
        return -1;
    }

    while ((ch = fgetc(stream)) != EOF && ch != '\n') {
        if (length == SIZE_MAX - 1) {
            free(buffer);
            return -1;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;

            if (capacity == 0) {
                new_capacity = 128;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(buffer);
                    return -1;
                }
                new_capacity = capacity * 2;
            }

            char *new_buffer = realloc(buffer, new_capacity);

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

    if (buffer == NULL) {
        buffer = malloc(1);
        if (buffer == NULL) {
            return -1;
        }
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