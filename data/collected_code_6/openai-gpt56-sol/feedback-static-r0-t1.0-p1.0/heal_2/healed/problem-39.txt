#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 128U

static bool can_rearrange_without_equal_adjacent(const char *str, size_t length)
{
    size_t frequencies[256] = {0};
    size_t max_frequency = 0;

    if (str == NULL) {
        return false;
    }

    for (size_t i = 0; i < length; ++i) {
        unsigned char character = (unsigned char)str[i];

        ++frequencies[character];
        if (frequencies[character] > max_frequency) {
            max_frequency = frequencies[character];
        }
    }

    return max_frequency <= (length / 2U) + (length % 2U);
}

static int read_line(FILE *stream, char **line, size_t *length)
{
    size_t capacity = INITIAL_CAPACITY;
    char *buffer;
    int character;

    if (stream == NULL || line == NULL || length == NULL) {
        return -1;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    *length = 0;

    while ((character = fgetc(stream)) != EOF && character != '\n') {
        if (*length == capacity - 1U) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2U) {
                free(buffer);
                return -1;
            }

            new_capacity = capacity * 2U;
            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return -1;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[(*length)++] = (char)character;
    }

    if (ferror(stream)) {
        free(buffer);
        return -1;
    }

    if (character == EOF && *length == 0U) {
        free(buffer);
        *line = NULL;
        return 0;
    }

    if (*length > 0U && buffer[*length - 1U] == '\r') {
        --(*length);
    }

    buffer[*length] = '\0';
    *line = buffer;
    return 1;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;
    int status = read_line(stdin, &input, &length);

    if (status < 0) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (status == 0) {
        return EXIT_SUCCESS;
    }

    if (puts(can_rearrange_without_equal_adjacent(input, length)
                 ? "true"
                 : "false") == EOF) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}