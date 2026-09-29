#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 128U

static bool can_rearrange_without_adjacent_duplicates(
    const unsigned char *string,
    size_t length)
{
    size_t frequencies[UCHAR_MAX + 1U] = {0};
    size_t maximum = 0U;

    if (string == NULL && length != 0U) {
        return false;
    }

    for (size_t i = 0U; i < length; ++i) {
        size_t frequency = ++frequencies[string[i]];

        if (frequency > maximum) {
            maximum = frequency;
        }
    }

    return maximum <= (length / 2U) + (length % 2U);
}

static bool read_line(FILE *stream, unsigned char **buffer, size_t *length)
{
    size_t capacity = INITIAL_CAPACITY;
    unsigned char *data = malloc(capacity);

    if (stream == NULL || buffer == NULL || length == NULL || data == NULL) {
        free(data);
        return false;
    }

    *buffer = NULL;
    *length = 0U;

    for (;;) {
        int character = fgetc(stream);

        if (character == EOF) {
            if (ferror(stream) || *length == 0U) {
                free(data);
                return false;
            }
            break;
        }

        if (character == '\n') {
            break;
        }

        if (*length == capacity) {
            if (capacity > SIZE_MAX / 2U) {
                free(data);
                return false;
            }

            size_t new_capacity = capacity * 2U;
            unsigned char *resized = realloc(data, new_capacity);

            if (resized == NULL) {
                free(data);
                return false;
            }

            data = resized;
            capacity = new_capacity;
        }

        data[(*length)++] = (unsigned char)character;
    }

    if (*length > 0U && data[*length - 1U] == (unsigned char)'\r') {
        --*length;
    }

    *buffer = data;
    return true;
}

int main(void)
{
    unsigned char *input = NULL;
    size_t length = 0U;

    if (!read_line(stdin, &input, &length)) {
        return EXIT_FAILURE;
    }

    if (puts(can_rearrange_without_adjacent_duplicates(input, length)
                 ? "true"
                 : "false") == EOF) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}