#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_SEQUENCE_LENGTH 4095U

static int discard_line(void)
{
    int character;

    while ((character = fgetc(stdin)) != '\n' && character != EOF) {
    }

    return character;
}

static int read_sequence(char **sequence, size_t *sequence_length)
{
    const size_t capacity = (size_t)MAX_SEQUENCE_LENGTH + 2U;
    char *buffer;
    size_t length;
    int character;

    if (sequence == NULL || sequence_length == NULL ||
        capacity > (size_t)INT_MAX) {
        return -1;
    }

    *sequence = NULL;
    *sequence_length = 0U;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    if (fgets(buffer, (int)capacity, stdin) == NULL) {
        free(buffer);
        return -1;
    }

    length = strcspn(buffer, "\r\n");

    if (buffer[length] == '\r') {
        buffer[length] = '\0';

        if (buffer[length + 1U] == '\n') {
            buffer[length + 1U] = '\0';
        } else {
            character = fgetc(stdin);
            if (character != '\n' && character != EOF) {
                discard_line();
            }
        }
    } else if (buffer[length] == '\n') {
        buffer[length] = '\0';
    } else {
        character = fgetc(stdin);

        if (character != '\n' && character != EOF) {
            discard_line();
            free(buffer);
            return 1;
        }

        buffer[length] = '\0';
    }

    if (length > (size_t)MAX_SEQUENCE_LENGTH) {
        free(buffer);
        return 1;
    }

    *sequence = buffer;
    *sequence_length = length;
    return 0;
}

static char *longest_common_subsequence(const char *first,
                                        size_t first_length,
                                        const char *second,
                                        size_t second_length)
{
    size_t rows;
    size_t columns;
    size_t cells;
    size_t *table;
    char *result;
    size_t length;
    size_t position;
    size_t i;
    size_t j;

    if (first == NULL || second == NULL ||
        first_length == SIZE_MAX || second_length == SIZE_MAX) {
        return NULL;
    }

    rows = first_length + 1U;
    columns = second_length + 1U;

    if (rows > SIZE_MAX / columns) {
        return NULL;
    }

    cells = rows * columns;

    if (cells > SIZE_MAX / sizeof(*table)) {
        return NULL;
    }

    table = calloc(cells, sizeof(*table));
    if (table == NULL) {
        return NULL;
    }

    for (i = 1U; i < rows; ++i) {
        for (j = 1U; j < columns; ++j) {
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

    length = table[first_length * columns + second_length];

    if (length == SIZE_MAX) {
        free(table);
        return NULL;
    }

    result = malloc(length + 1U);
    if (result == NULL) {
        free(table);
        return NULL;
    }

    result[length] = '\0';
    position = length;
    i = first_length;
    j = second_length;

    while (i > 0U && j > 0U) {
        if (first[i - 1U] == second[j - 1U]) {
            --position;
            result[position] = first[i - 1U];
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
    return result;
}

int main(void)
{
    char *first = NULL;
    char *second = NULL;
    char *result = NULL;
    size_t first_length = 0U;
    size_t second_length = 0U;
    int status;
    int exit_status = EXIT_FAILURE;

    status = read_sequence(&first, &first_length);
    if (status != 0) {
        fputs(status > 0
                  ? "The first sequence is too long.\n"
                  : "Failed to read the first sequence.\n",
              stderr);
        goto cleanup;
    }

    status = read_sequence(&second, &second_length);
    if (status != 0) {
        fputs(status > 0
                  ? "The second sequence is too long.\n"
                  : "Failed to read the second sequence.\n",
              stderr);
        goto cleanup;
    }

    result = longest_common_subsequence(first, first_length,
                                        second, second_length);
    if (result == NULL) {
        fputs("Unable to compute the longest common subsequence.\n", stderr);
        goto cleanup;
    }

    if (fputs(result, stdout) == EOF || fputc('\n', stdout) == EOF) {
        goto cleanup;
    }

    exit_status = EXIT_SUCCESS;

cleanup:
    free(result);
    free(second);
    free(first);
    return exit_status;
}