#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int ends_with_alphanumeric(const char *string, bool *result)
{
    const unsigned char *cursor;
    const unsigned char *last = NULL;

    if (string == NULL || result == NULL) {
        return -1;
    }

    for (cursor = (const unsigned char *)string; *cursor != '\0'; ++cursor) {
        last = cursor;
    }

    *result = last != NULL && isalnum(*last) != 0;
    return 0;
}

static char *read_line(FILE *stream)
{
    char *buffer;
    size_t length = 0;
    size_t capacity = 128;

    if (stream == NULL) {
        return NULL;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return NULL;
    }

    for (;;) {
        size_t available;
        size_t bytes_read = 0;

        available = capacity - length;

        if (available < 2) {
            size_t new_capacity;
            char *resized;

            if (capacity >= (size_t)INT_MAX) {
                free(buffer);
                return NULL;
            }

            new_capacity = capacity > (size_t)INT_MAX / 2
                               ? (size_t)INT_MAX
                               : capacity * 2;

            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return NULL;
            }

            buffer = resized;
            capacity = new_capacity;
            available = capacity - length;
        }

        if (fgets(buffer + length, (int)available, stream) == NULL) {
            if (ferror(stream) || length == 0) {
                free(buffer);
                return NULL;
            }

            buffer[length] = '\0';
            return buffer;
        }

        while (buffer[length + bytes_read] != '\0' &&
               buffer[length + bytes_read] != '\n') {
            ++bytes_read;
        }

        length += bytes_read;

        if (buffer[length] == '\n') {
            buffer[length] = '\0';
            return buffer;
        }

        if (feof(stream)) {
            buffer[length] = '\0';
            return buffer;
        }
    }
}

int main(void)
{
    char *input;
    bool result;

    input = read_line(stdin);
    if (input == NULL) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (ends_with_alphanumeric(input, &result) != 0) {
        free(input);
        fputs("Operation failed.\n", stderr);
        return EXIT_FAILURE;
    }

    puts(result ? "true" : "false");
    free(input);

    return EXIT_SUCCESS;
}