#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool can_rearrange_without_adjacent_duplicates(
    const unsigned char *str,
    size_t length)
{
    size_t frequencies[256] = {0};
    size_t max_frequency = 0;

    if (str == NULL && length != 0) {
        return false;
    }

    for (size_t i = 0; i < length; ++i) {
        size_t frequency = ++frequencies[str[i]];

        if (frequency > max_frequency) {
            max_frequency = frequency;
        }
    }

    return max_frequency <= (length / 2) + (length % 2);
}

static unsigned char *read_line(size_t *length)
{
    const size_t initial_capacity = 128;
    unsigned char *buffer = NULL;
    size_t capacity = initial_capacity;
    size_t used = 0;
    int character;

    if (length == NULL) {
        return NULL;
    }

    *length = 0;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return NULL;
    }

    for (;;) {
        character = fgetc(stdin);

        if (character == EOF || character == '\n') {
            break;
        }

        if (used >= capacity) {
            size_t new_capacity;
            unsigned char *new_buffer;

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

        buffer[used++] = (unsigned char)character;
    }

    if (ferror(stdin)) {
        free(buffer);
        return NULL;
    }

    if (character == EOF && used == 0) {
        free(buffer);
        return NULL;
    }

    if (used > 0 && buffer[used - 1] == '\r') {
        --used;
    }

    *length = used;
    return buffer;
}

int main(void)
{
    size_t length = 0;
    unsigned char *input = read_line(&length);

    if (input == NULL) {
        return feof(stdin) && !ferror(stdin) ? EXIT_SUCCESS : EXIT_FAILURE;
    }

    puts(can_rearrange_without_adjacent_duplicates(input, length)
             ? "true"
             : "false");

    free(input);
    return EXIT_SUCCESS;
}