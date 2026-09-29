#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int count_lists(const char *tuple, size_t *count)
{
    size_t lists = 0;
    unsigned char quote = 0;
    int escaped = 0;
    const unsigned char *p;

    if (tuple == NULL || count == NULL) {
        return -1;
    }

    for (p = (const unsigned char *)tuple; *p != '\0'; ++p) {
        if (quote != 0) {
            if (escaped) {
                escaped = 0;
            } else if (*p == '\\') {
                escaped = 1;
            } else if (*p == quote) {
                quote = 0;
            }
        } else if (*p == '\'' || *p == '"') {
            quote = *p;
        } else if (*p == '[') {
            if (lists == SIZE_MAX) {
                return -1;
            }
            ++lists;
        }
    }

    if (quote != 0 || escaped) {
        return -1;
    }

    *count = lists;
    return 0;
}

static int read_line(FILE *stream, char **line)
{
    enum { CHUNK_SIZE = 128 };
    char *buffer;
    size_t capacity = CHUNK_SIZE;
    size_t length = 0;

    if (stream == NULL || line == NULL) {
        return -1;
    }

    *line = NULL;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    for (;;) {
        size_t available = capacity - length;

        if (available < 2) {
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
            available = capacity - length;
        }

        if (fgets(buffer + length, (int)(available > INT32_MAX
                                           ? INT32_MAX
                                           : available),
                  stream) == NULL) {
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
            buffer[length] = '\0';
            *line = buffer;
            return 0;
        }

        if (feof(stream)) {
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

    if (count_lists(input, &count) != 0) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);

    if (printf("%zu\n", count) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}