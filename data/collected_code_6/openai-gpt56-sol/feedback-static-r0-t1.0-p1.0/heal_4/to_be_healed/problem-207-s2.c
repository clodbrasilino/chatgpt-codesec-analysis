#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int longest_repeating_subsequence(const char *str, size_t length,
                                         size_t *result)
{
    size_t columns;
    size_t *previous;
    size_t *current;

    if (result == NULL || (str == NULL && length != 0) ||
        length == SIZE_MAX) {
        return -1;
    }

    columns = length + 1;

    if (columns > SIZE_MAX / sizeof(*previous)) {
        return -1;
    }

    previous = calloc(columns, sizeof(*previous));
    current = calloc(columns, sizeof(*current));

    if (previous == NULL || current == NULL) {
        free(previous);
        free(current);
        return -1;
    }

    for (size_t i = 1; i <= length; ++i) {
        current[0] = 0;

        for (size_t j = 1; j <= length; ++j) {
            if (i != j && str[i - 1] == str[j - 1]) {
                current[j] = previous[j - 1] + 1;
            } else {
                current[j] = previous[j] > current[j - 1]
                                 ? previous[j]
                                 : current[j - 1];
            }
        }

        size_t *temporary = previous;
        previous = current;
        current = temporary;
    }

    *result = previous[length];

    free(previous);
    free(current);
    return 0;
}

static int read_line(FILE *stream, char **line, size_t *length)
{
    char *buffer = NULL;
    size_t capacity = 0;
    size_t used = 0;
    int ch;

    if (stream == NULL || line == NULL || length == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stream)) != EOF && ch != '\n') {
        if (used == capacity) {
            size_t new_capacity;

            if (capacity == 0) {
                new_capacity = 64;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(buffer);
                    return -1;
                }
                new_capacity = capacity * 2;
            }

            if (new_capacity > SIZE_MAX / sizeof(*buffer)) {
                free(buffer);
                return -1;
            }

            char *new_buffer = realloc(buffer,
                                       new_capacity * sizeof(*buffer));
            if (new_buffer == NULL) {
                free(buffer);
                return -1;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[used++] = (char)ch;
    }

    if (ferror(stream)) {
        free(buffer);
        return -1;
    }

    *line = buffer;
    *length = used;
    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;
    size_t result = 0;
    int status = EXIT_FAILURE;

    if (read_line(stdin, &input, &length) != 0) {
        goto cleanup;
    }

    if (longest_repeating_subsequence(input, length, &result) != 0) {
        goto cleanup;
    }

    if (printf("%zu\n", result) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(input);
    return status;
}