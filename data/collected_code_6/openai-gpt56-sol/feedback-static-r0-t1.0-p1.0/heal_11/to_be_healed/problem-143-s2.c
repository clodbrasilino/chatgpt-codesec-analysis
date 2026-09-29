#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int count_lists_in_tuple(const char *tuple, size_t *count)
{
    size_t lists = 0;
    size_t square_depth = 0;
    char quote = '\0';
    int escaped = 0;

    if (tuple == NULL || count == NULL) {
        return -1;
    }

    for (size_t i = 0; tuple[i] != '\0'; ++i) {
        unsigned char ch = (unsigned char)tuple[i];

        if (quote != '\0') {
            if (escaped) {
                escaped = 0;
            } else if (ch == (unsigned char)'\\') {
                escaped = 1;
            } else if (ch == (unsigned char)quote) {
                quote = '\0';
            }
            continue;
        }

        if (ch == (unsigned char)'\'' || ch == (unsigned char)'"') {
            quote = (char)ch;
        } else if (ch == (unsigned char)'[') {
            if (square_depth == 0) {
                if (lists == SIZE_MAX) {
                    return -1;
                }
                ++lists;
            }

            if (square_depth == SIZE_MAX) {
                return -1;
            }
            ++square_depth;
        } else if (ch == (unsigned char)']') {
            if (square_depth == 0) {
                return -1;
            }
            --square_depth;
        }
    }

    if (quote != '\0' || escaped || square_depth != 0) {
        return -1;
    }

    *count = lists;
    return 0;
}

static int read_line(FILE *stream, char **line)
{
    size_t capacity = 128;
    size_t length = 0;
    char *buffer;

    if (stream == NULL || line == NULL) {
        return -1;
    }

    *line = NULL;
    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char chunk[4096];

        if (fgets(chunk, sizeof chunk, stream) == NULL) {
            if (ferror(stream) || length == 0) {
                free(buffer);
                return -1;
            }
            break;
        }

        size_t chunk_length = 0;
        while (chunk_length < sizeof chunk &&
               chunk[chunk_length] != '\0' &&
               chunk[chunk_length] != '\n') {
            ++chunk_length;
        }

        if (chunk_length > SIZE_MAX - length - 1) {
            free(buffer);
            return -1;
        }

        size_t required = length + chunk_length + 1;
        if (required > capacity) {
            size_t new_capacity = capacity;

            while (new_capacity < required) {
                if (new_capacity > SIZE_MAX / 2) {
                    new_capacity = required;
                    break;
                }
                new_capacity *= 2;
            }

            char *new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return -1;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        for (size_t i = 0; i < chunk_length; ++i) {
            buffer[length + i] = chunk[i];
        }
        length += chunk_length;

        if (chunk[chunk_length] == '\n') {
            break;
        }

        if (chunk_length < sizeof chunk - 1) {
            break;
        }
    }

    buffer[length] = '\0';
    *line = buffer;
    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t count = 0;

    if (read_line(stdin, &input) != 0) {
        return EXIT_FAILURE;
    }

    if (count_lists_in_tuple(input, &count) != 0) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);

    if (printf("%zu\n", count) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}