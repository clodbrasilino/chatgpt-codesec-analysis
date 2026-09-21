#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

enum { INITIAL_CAPACITY = 128 };

static bool first_and_last_are_equal(const char *string, size_t length)
{
    return string != NULL && length != 0U &&
           string[0] == string[length - 1U];
}

static int grow_buffer(char **buffer, size_t *capacity)
{
    size_t new_capacity;
    char *resized;

    if (buffer == NULL || *buffer == NULL || capacity == NULL ||
        *capacity == 0U || *capacity > SIZE_MAX / 2U) {
        return -1;
    }

    new_capacity = *capacity * 2U;
    resized = realloc(*buffer, new_capacity);

    if (resized == NULL) {
        return -1;
    }

    *buffer = resized;
    *capacity = new_capacity;
    return 0;
}

static int read_line(FILE *stream, char **buffer, size_t *length)
{
    char *data;
    size_t capacity = INITIAL_CAPACITY;
    size_t used = 0U;

    if (stream == NULL || buffer == NULL || length == NULL) {
        return -1;
    }

    *buffer = NULL;
    *length = 0U;

    data = malloc(capacity);
    if (data == NULL) {
        return -1;
    }

    for (;;) {
        int character;

        if (used == capacity && grow_buffer(&data, &capacity) != 0) {
            free(data);
            return -1;
        }

        character = fgetc(stream);

        if (character == EOF) {
            if (ferror(stream)) {
                free(data);
                return -1;
            }
            break;
        }

        if (character == '\n') {
            break;
        }

        if (character == '\r') {
            int next = fgetc(stream);

            if (next == EOF) {
                if (ferror(stream)) {
                    free(data);
                    return -1;
                }
            } else if (next != '\n') {
                if (ungetc(next, stream) == EOF) {
                    free(data);
                    return -1;
                }
            }

            break;
        }

        data[used++] = (char)(unsigned char)character;
    }

    if (used == 0U && feof(stream)) {
        free(data);
        return 0;
    }

    *buffer = data;
    *length = used;
    return 1;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0U;
    int status = read_line(stdin, &input, &length);

    if (status == 0) {
        return EXIT_FAILURE;
    }

    if (status < 0) {
        fputs("Input error\n", stderr);
        return EXIT_FAILURE;
    }

    puts(first_and_last_are_equal(input, length) ? "Equal" : "Not equal");

    free(input);
    return EXIT_SUCCESS;
}