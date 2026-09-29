#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

enum { INITIAL_CAPACITY = 256 };

static bool is_concatenation_of_another_string(const char *str, size_t length)
{
    if (str == NULL || length < 2U) {
        return false;
    }

    for (size_t pattern_length = 1U;
         pattern_length <= length / 2U;
         ++pattern_length) {
        if (length % pattern_length != 0U) {
            continue;
        }

        size_t i = pattern_length;

        while (i < length && str[i] == str[i % pattern_length]) {
            ++i;
        }

        if (i == length) {
            return true;
        }
    }

    return false;
}

static char *read_line(FILE *stream, size_t *length)
{
    if (stream == NULL || length == NULL) {
        return NULL;
    }

    *length = 0U;

    size_t capacity = INITIAL_CAPACITY;
    char *buffer = malloc(capacity);

    if (buffer == NULL) {
        return NULL;
    }

    size_t used = 0U;

    for (;;) {
        if (used == capacity - 1U) {
            if (capacity > SIZE_MAX / 2U) {
                free(buffer);
                return NULL;
            }

            size_t new_capacity = capacity * 2U;
            char *new_buffer = realloc(buffer, new_capacity);

            if (new_buffer == NULL) {
                free(buffer);
                return NULL;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        size_t available = capacity - used - 1U;

        if (fgets(buffer + used, (int)(available + 1U), stream) == NULL) {
            if (ferror(stream)) {
                free(buffer);
                return NULL;
            }
            break;
        }

        size_t read_count = 0U;

        while (read_count < available &&
               buffer[used + read_count] != '\0' &&
               buffer[used + read_count] != '\n') {
            ++read_count;
        }

        if (read_count < available && buffer[used + read_count] == '\n') {
            used += read_count;
            break;
        }

        used += read_count;

        if (read_count < available) {
            break;
        }
    }

    if (used > 0U && buffer[used - 1U] == '\r') {
        --used;
    }

    buffer[used] = '\0';
    *length = used;

    return buffer;
}

int main(void)
{
    size_t length = 0U;
    char *input = read_line(stdin, &length);

    if (input == NULL) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    puts(is_concatenation_of_another_string(input, length)
             ? "true"
             : "false");

    free(input);
    return EXIT_SUCCESS;
}