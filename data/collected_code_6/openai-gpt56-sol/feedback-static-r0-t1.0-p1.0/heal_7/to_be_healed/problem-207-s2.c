#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

static int grow_buffer(char **buffer, size_t *capacity, size_t required)
{
    size_t new_capacity;
    char *new_buffer;

    if (buffer == NULL || capacity == NULL) {
        return -1;
    }

    if (required <= *capacity) {
        return 0;
    }

    new_capacity = *capacity == 0 ? 64 : *capacity;

    while (new_capacity < required) {
        if (new_capacity > SIZE_MAX / 2) {
            new_capacity = required;
            break;
        }

        new_capacity *= 2;
    }

    if (new_capacity < required) {
        return -1;
    }

    new_buffer = realloc(*buffer, new_capacity);
    if (new_buffer == NULL) {
        return -1;
    }

    *buffer = new_buffer;
    *capacity = new_capacity;
    return 0;
}

static int read_line(FILE *stream, char **line, size_t *length)
{
    char *buffer = NULL;
    size_t capacity = 0;
    size_t used = 0;

    if (stream == NULL || line == NULL || length == NULL) {
        return -1;
    }

    *line = NULL;
    *length = 0;

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int value = fgetc(stream);

        if (value == '\n' || value == EOF) {
            if (value == EOF && ferror(stream)) {
                free(buffer);
                return -1;
            }
            break;
        }

        if (used == SIZE_MAX ||
            grow_buffer(&buffer, &capacity, used + 1) != 0) {
            free(buffer);
            return -1;
        }

        buffer[used++] = (char)(unsigned char)value;
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