#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int minimum_rotations(const unsigned char *string, size_t length,
                             size_t *result)
{
    size_t *prefix;
    size_t matched = 0;
    size_t period;

    if (result == NULL) {
        return -1;
    }

    if (length == 0) {
        *result = 0;
        return 0;
    }

    if (string == NULL || length > SIZE_MAX / sizeof(*prefix)) {
        return -1;
    }

    prefix = malloc(length * sizeof(*prefix));
    if (prefix == NULL) {
        return -1;
    }

    prefix[0] = 0;

    for (size_t index = 1; index < length; ++index) {
        while (matched > 0 && string[index] != string[matched]) {
            matched = prefix[matched - 1];
        }

        if (string[index] == string[matched]) {
            ++matched;
        }

        prefix[index] = matched;
    }

    period = length - prefix[length - 1];
    *result = (length % period == 0) ? period : length;

    free(prefix);
    return 0;
}

static int read_line(FILE *stream, unsigned char **buffer, size_t *length)
{
    unsigned char *data = NULL;
    size_t capacity = 0;
    size_t used = 0;
    int character;

    if (stream == NULL || buffer == NULL || length == NULL) {
        return -1;
    }

    while ((character = fgetc(stream)) != EOF && character != '\n') {
        if (used == capacity) {
            size_t new_capacity;
            unsigned char *resized;

            if (capacity == 0) {
                new_capacity = 64;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(data);
                    return -1;
                }
                new_capacity = capacity * 2;
            }

            if (new_capacity > SIZE_MAX / sizeof(*data)) {
                free(data);
                return -1;
            }

            resized = realloc(data, new_capacity * sizeof(*data));
            if (resized == NULL) {
                free(data);
                return -1;
            }

            data = resized;
            capacity = new_capacity;
        }

        data[used++] = (unsigned char)character;
    }

    if (character == EOF && ferror(stream)) {
        free(data);
        return -1;
    }

    *buffer = data;
    *length = used;
    return 0;
}

int main(void)
{
    unsigned char *input = NULL;
    size_t length = 0;
    size_t result;

    if (read_line(stdin, &input, &length) != 0) {
        return EXIT_FAILURE;
    }

    if (minimum_rotations(input, length, &result) != 0) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);

    if (printf("%zu\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}