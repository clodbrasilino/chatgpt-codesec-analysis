#include <stdio.h>
#include <stdlib.h>

static int count_lists_in_tuple(const char *tuple, size_t *count)
{
    size_t lists = 0;
    size_t square_depth = 0;
    int in_string = 0;
    int escaped = 0;
    char quote = '\0';

    if (tuple == NULL || count == NULL) {
        return -1;
    }

    for (const unsigned char *p = (const unsigned char *)tuple; *p != '\0'; ++p) {
        unsigned char ch = *p;

        if (in_string) {
            if (escaped) {
                escaped = 0;
            } else if (ch == '\\') {
                escaped = 1;
            } else if (ch == (unsigned char)quote) {
                in_string = 0;
            }
            continue;
        }

        if (ch == '\'' || ch == '"') {
            in_string = 1;
            quote = (char)ch;
        } else if (ch == '[') {
            if (square_depth == 0) {
                ++lists;
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
    size_t capacity = 128;
    size_t length = 0;
    char *buffer = malloc(capacity);

    if (buffer == NULL) {
        return NULL;
    }

    for (;;) {
        int ch = fgetc(stream);

        if (ch == EOF) {
            if (ferror(stream) || length == 0) {
                free(buffer);
                return NULL;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > (size_t)-1 / 2) {
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

        buffer[length++] = (char)ch;
    }

    buffer[length] = '\0';
    return buffer;
}

int main(void)
{
    char *tuple = read_line(stdin);
    size_t count = 0;

    if (tuple == NULL) {
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