#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int longest_repeating_subsequence(const unsigned char *str,
                                         size_t length,
                                         size_t *result)
{
    size_t columns;
    size_t cells;
    size_t *table;

    if (str == NULL || result == NULL || length == SIZE_MAX) {
        return -1;
    }

    columns = length + 1;

    if (columns > SIZE_MAX / columns) {
        return -1;
    }

    cells = columns * columns;

    if (cells > SIZE_MAX / sizeof(*table)) {
        return -1;
    }

    table = calloc(cells, sizeof(*table));
    if (table == NULL) {
        return -1;
    }

    for (size_t i = 1; i <= length; ++i) {
        for (size_t j = 1; j <= length; ++j) {
            size_t current = i * columns + j;

            if (str[i - 1] == str[j - 1] && i != j) {
                table[current] =
                    table[(i - 1) * columns + (j - 1)] + 1;
            } else {
                size_t above = table[(i - 1) * columns + j];
                size_t left = table[i * columns + (j - 1)];

                table[current] = above > left ? above : left;
            }
        }
    }

    *result = table[length * columns + length];
    free(table);
    return 0;
}

static int read_line(FILE *stream, unsigned char **buffer, size_t *length)
{
    unsigned char *data = NULL;
    size_t used = 0;
    size_t capacity = 0;
    int character;

    if (stream == NULL || buffer == NULL || length == NULL) {
        return -1;
    }

    while ((character = fgetc(stream)) != EOF && character != '\n') {
        if (used == capacity) {
            size_t new_capacity;
            unsigned char *new_data;

            if (capacity == 0) {
                new_capacity = 64;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(data);
                    return -1;
                }
                new_capacity = capacity * 2;
            }

            new_data = realloc(data, new_capacity);
            if (new_data == NULL) {
                free(data);
                return -1;
            }

            data = new_data;
            capacity = new_capacity;
        }

        data[used++] = (unsigned char)character;
    }

    if (ferror(stream)) {
        free(data);
        return -1;
    }

    if (data == NULL) {
        data = malloc(1);
        if (data == NULL) {
            return -1;
        }
    }

    *buffer = data;
    *length = used;
    return 0;
}

int main(void)
{
    unsigned char *input = NULL;
    size_t length = 0;
    size_t result;
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