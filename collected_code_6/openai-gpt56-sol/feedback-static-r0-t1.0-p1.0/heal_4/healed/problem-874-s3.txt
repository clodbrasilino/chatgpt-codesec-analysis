#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

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

        size_t index = pattern_length;

        while (index < length &&
               str[index] == str[index % pattern_length]) {
            ++index;
        }

        if (index == length) {
            return true;
        }
    }

    return false;
}

static bool read_line(FILE *stream, char **line, size_t *length)
{
    if (stream == NULL || line == NULL || length == NULL) {
        return false;
    }

    *line = NULL;
    *length = 0U;

    size_t capacity = 128U;
    size_t used = 0U;
    char *buffer = malloc(capacity);

    if (buffer == NULL) {
        return false;
    }

    for (;;) {
        int character = fgetc(stream);

        if (character == EOF) {
            if (ferror(stream) || used == 0U) {
                free(buffer);
                return false;
            }
            break;
        }

        if (character == '\n') {
            break;
        }

        if (used == capacity) {
            if (capacity > SIZE_MAX / 2U) {
                free(buffer);
                return false;
            }

            size_t new_capacity = capacity * 2U;
            char *new_buffer = realloc(buffer, new_capacity);

            if (new_buffer == NULL) {
                free(buffer);
                return false;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[used++] = (char)(unsigned char)character;
    }

    *line = buffer;
    *length = used;
    return true;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0U;

    if (!read_line(stdin, &input, &length)) {
        return EXIT_FAILURE;
    }

    puts(is_concatenation_of_another_string(input, length)
             ? "true"
             : "false");

    free(input);
    return EXIT_SUCCESS;
}