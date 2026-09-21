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
            } else if (ch == '\\') {
                escaped = 1;
            } else if (ch == (unsigned char)quote) {
                quote = '\0';
            }
            continue;
        }

        if (ch == '\'' || ch == '"') {
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

    if (quote != '\0' || square_depth != 0) {
        return -1;
    }

    *count = lists;
    return 0;
}

static int read_line(FILE *stream, char **line)
{
    char *buffer = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int ch;

    if (stream == NULL || line == NULL) {
        return -1;
    }

    while ((ch = fgetc(stream)) != EOF && ch != '\n') {
        if (length == capacity) {
            size_t new_capacity;

            if (capacity == 0) {
                new_capacity = 128;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(buffer);
                    return -1;
                }
                new_capacity = capacity * 2;
            }

            char *resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return -1;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    if (ferror(stream) || (ch == EOF && length == 0)) {
        free(buffer);
        return -1;
    }

    if (length == SIZE_MAX) {
        free(buffer);
        return -1;
    }

    if (capacity <= length) {
        char *resized = realloc(buffer, length + 1);
        if (resized == NULL) {
            free(buffer);
            return -1;
        }
        buffer = resized;
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