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

static int read_line(char **line)
{
    char *buffer = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int ch;

    if (line == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != '\n' && ch != EOF) {
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

            char *new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return -1;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    if (ferror(stdin) || (ch == EOF && length == 0)) {
        free(buffer);
        return -1;
    }

    if (length == SIZE_MAX) {
        free(buffer);
        return -1;
    }

    char *new_buffer = realloc(buffer, length + 1);
    if (new_buffer == NULL) {
        free(buffer);
        return -1;
    }

    buffer = new_buffer;
    buffer[length] = '\0';
    *line = buffer;

    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t count = 0;

    if (read_line(&input) != 0) {
        return EXIT_FAILURE;
    }

    if (count_lists_in_tuple(input, &count) != 0) {
        free(input);
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", count) < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}