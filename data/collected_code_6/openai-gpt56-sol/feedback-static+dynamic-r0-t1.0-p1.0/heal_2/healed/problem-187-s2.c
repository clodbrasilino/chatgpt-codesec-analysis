#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MAX_SEQUENCE_LENGTH 4095U

enum read_status {
    READ_OK = 0,
    READ_TOO_LONG,
    READ_EOF,
    READ_ERROR
};

static enum read_status read_sequence(FILE *stream, char **sequence,
                                      size_t *sequence_length)
{
    char *buffer;
    size_t capacity = 128U;
    size_t length = 0U;
    int ch;

    if (stream == NULL || sequence == NULL || sequence_length == NULL) {
        return READ_ERROR;
    }

    *sequence = NULL;
    *sequence_length = 0U;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return READ_ERROR;
    }

    for (;;) {
        ch = fgetc(stream);

        if (ch == '\n' || ch == EOF) {
            break;
        }

        if (length == MAX_SEQUENCE_LENGTH) {
            do {
                ch = fgetc(stream);
            } while (ch != '\n' && ch != EOF);

            if (ch == EOF && ferror(stream)) {
                free(buffer);
                return READ_ERROR;
            }

            free(buffer);
            return READ_TOO_LONG;
        }

        if (length + 1U >= capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity > (MAX_SEQUENCE_LENGTH + 1U) / 2U) {
                new_capacity = MAX_SEQUENCE_LENGTH + 1U;
            } else {
                new_capacity = capacity * 2U;
            }

            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return READ_ERROR;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    if (ch == EOF) {
        if (ferror(stream)) {
            free(buffer);
            return READ_ERROR;
        }

        if (length == 0U) {
            free(buffer);
            return READ_EOF;
        }
    }

    buffer[length] = '\0';
    *sequence = buffer;
    *sequence_length = length;
    return READ_OK;
}

static int longest_common_subsequence(const char *first, size_t first_len,
                                      const char *second, size_t second_len,
                                      char **result)
{
    size_t rows;
    size_t columns;
    size_t cells;
    size_t *table;
    char *sequence;
    size_t length;
    size_t position;
    size_t i;
    size_t j;

    if (first == NULL || second == NULL || result == NULL) {
        return -1;
    }

    *result = NULL;

    if (first_len == SIZE_MAX || second_len == SIZE_MAX) {
        return -1;
    }

    rows = first_len + 1U;
    columns = second_len + 1U;

    if (rows > SIZE_MAX / columns) {
        return -1;
    }

    cells = rows * columns;

    if (cells > SIZE_MAX / sizeof(*table)) {
        return -1;
    }

    table = calloc(cells, sizeof(*table));
    if (table == NULL) {
        return -1;
    }

    for (i = 1U; i <= first_len; ++i) {
        for (j = 1U; j <= second_len; ++j) {
            size_t index = i * columns + j;

            if (first[i - 1U] == second[j - 1U]) {
                table[index] =
                    table[(i - 1U) * columns + (j - 1U)] + 1U;
            } else {
                size_t above = table[(i - 1U) * columns + j];
                size_t left = table[i * columns + (j - 1U)];

                table[index] = above >= left ? above : left;
            }
        }
    }

    length = table[first_len * columns + second_len];
    sequence = malloc(length + 1U);

    if (sequence == NULL) {
        free(table);
        return -1;
    }

    position = length;
    sequence[position] = '\0';
    i = first_len;
    j = second_len;

    while (i > 0U && j > 0U) {
        if (first[i - 1U] == second[j - 1U]) {
            sequence[--position] = first[i - 1U];
            --i;
            --j;
        } else if (table[(i - 1U) * columns + j] >=
                   table[i * columns + (j - 1U)]) {
            --i;
        } else {
            --j;
        }
    }

    free(table);
    *result = sequence;
    return 0;
}

int main(void)
{
    char *first = NULL;
    char *second = NULL;
    char *lcs = NULL;
    size_t first_len = 0U;
    size_t second_len = 0U;
    enum read_status status;
    int exit_status = EXIT_FAILURE;

    status = read_sequence(stdin, &first, &first_len);
    if (status != READ_OK) {
        if (status == READ_TOO_LONG) {
            fputs("The first sequence is too long.\n", stderr);
        } else {
            fputs("Failed to read the first sequence.\n", stderr);
        }
        goto cleanup;
    }

    status = read_sequence(stdin, &second, &second_len);
    if (status != READ_OK) {
        if (status == READ_TOO_LONG) {
            fputs("The second sequence is too long.\n", stderr);
        } else {
            fputs("Failed to read the second sequence.\n", stderr);
        }
        goto cleanup;
    }

    if (longest_common_subsequence(first, first_len, second, second_len,
                                   &lcs) != 0) {
        fputs("Failed to compute the longest common subsequence.\n", stderr);
        goto cleanup;
    }

    if (fputs(lcs, stdout) == EOF || fputc('\n', stdout) == EOF) {
        goto cleanup;
    }

    exit_status = EXIT_SUCCESS;

cleanup:
    free(lcs);
    free(second);
    free(first);
    return exit_status;
}