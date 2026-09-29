#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int count_lists_in_tuple(const char *tuple, size_t *count)
{
    size_t lists = 0;
    size_t square_depth = 0;
    int in_string = 0;
    int escaped = 0;
    unsigned char quote = '\0';
    const unsigned char *p;

    if (tuple == NULL || count == NULL) {
        return -1;
    }

    for (p = (const unsigned char *)tuple; *p != '\0'; ++p) {
        unsigned char ch = *p;

        if (in_string) {
            if (escaped) {
                escaped = 0;
            } else if (ch == '\\') {
                escaped = 1;
            } else if (ch == quote) {
                in_string = 0;
            }
            continue;
        }

        if (ch == '\'' || ch == '"') {
            in_string = 1;
            quote = ch;
        } else if (ch == '[') {
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
        } else if (ch == ']') {
            if (square_depth == 0) {
                return -1;
            }
            --square_depth;
        }
    }

    if (in_string || square_depth != 0) {
        return -1;
    }

    *count = lists;
    return 0;
}

static char *read_line(FILE *stream)
{
    size_t capacity = 256;
    size_t length = 0;
    char *buffer;

    if (stream == NULL) {
        return NULL;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return NULL;
    }

    buffer[0] = '\0';

    for (;;) {
        size_t available;
        int read_size;

        if (length >= capacity) {
            free(buffer);
            return NULL;
        }

        available = capacity - length;

        if (available < 2) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                if (capacity == SIZE_MAX) {
                    free(buffer);
                    return NULL;
                }
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2;
            }

            if (new_capacity <= capacity) {
                free(buffer);
                return NULL;
            }

            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return NULL;
            }

            buffer = new_buffer;
            capacity = new_capacity;
            available = capacity - length;
        }

        read_size = available > (size_t)INT_MAX
                        ? INT_MAX
                        : (int)available;

        if (fgets(buffer + length, read_size, stream) == NULL) {
            if (ferror(stream) || length == 0) {
                free(buffer);
                return NULL;
            }
            break;
        }

        while (buffer[length] != '\0' && buffer[length] != '\n') {
            ++length;
        }

        if (buffer[length] == '\n') {
            buffer[length] = '\0';
            break;
        }

        if (feof(stream)) {
            break;
        }
    }

    if (length > 0 && buffer[length - 1] == '\r') {
        buffer[--length] = '\0';
    }

    return buffer;
}

int main(void)
{
    char *tuple;
    size_t count = 0;

    tuple = read_line(stdin);
    if (tuple == NULL) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (count_lists_in_tuple(tuple, &count) != 0) {
        free(tuple);
        fputs("Invalid tuple representation.\n", stderr);
        return EXIT_FAILURE;
    }

    free(tuple);

    if (printf("%zu\n", count) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}