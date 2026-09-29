#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

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
        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return -1;
            }

            new_capacity = capacity * 2;
            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return -1;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        if (fgets(buffer + length, (int)(capacity - length), stream) == NULL) {
            if (ferror(stream) || length == 0) {
                free(buffer);
                return -1;
            }
            break;
        }

        while (buffer[length] != '\0' && buffer[length] != '\n') {
            ++length;
        }

        if (buffer[length] == '\n') {
            break;
        }

        if (feof(stream)) {
            break;
        }
    }

    if (length > 0 && buffer[length - 1] == '\r') {
        --length;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 0;
}

int main(void)
{
    char *tuple = NULL;
    size_t count = 0;

    if (read_line(stdin, &tuple) != 0) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (count_lists_in_tuple(tuple, &count) != 0) {
        fputs("Invalid tuple representation.\n", stderr);
        free(tuple);
        return EXIT_FAILURE;
    }

    free(tuple);

    if (printf("%zu\n", count) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}