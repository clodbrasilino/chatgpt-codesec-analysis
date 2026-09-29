#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MAX_SEQUENCE_LENGTH 4095U

enum read_status {
    READ_ERROR = -1,
    READ_MISSING = 0,
    READ_SUCCESS = 1,
    READ_TOO_LONG = 2
};

static int discard_line(void)
{
    int ch;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
    }

    return ch == EOF && ferror(stdin) ? READ_ERROR : READ_SUCCESS;
}

static int read_sequence(char **sequence, size_t *sequence_length)
{
    char *buffer;
    size_t length;
    int ch;

    if (sequence == NULL || sequence_length == NULL) {
        return READ_ERROR;
    }

    *sequence = NULL;
    *sequence_length = 0U;

    buffer = malloc((size_t)MAX_SEQUENCE_LENGTH + 1U);
    if (buffer == NULL) {
        return READ_ERROR;
    }

    length = 0U;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != EOF && ch != '\n' && ch != '\r') {
        if (length == (size_t)MAX_SEQUENCE_LENGTH) {
            int discard_status = discard_line();

            free(buffer);
            return discard_status == READ_ERROR ? READ_ERROR : READ_TOO_LONG;
        }

        buffer[length++] = (char)ch;
    }

    if (ch == EOF) {
        if (ferror(stdin)) {
            free(buffer);
            return READ_ERROR;
        }

        if (length == 0U) {
            free(buffer);
            return READ_MISSING;
        }
    } else if (ch == '\r') {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int next = fgetc(stdin);

        if (next == EOF) {
            if (ferror(stdin)) {
                free(buffer);
                return READ_ERROR;
            }
        } else if (next != '\n') {
            if (ungetc(next, stdin) == EOF) {
                free(buffer);
                return READ_ERROR;
            }
        }
    }

    buffer[length] = '\0';
    *sequence = buffer;
    *sequence_length = length;

    return READ_SUCCESS;
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
    size_t result_length;
    size_t position;
    size_t i;
    size_t j;

    if (first == NULL || second == NULL ||
        first_length > (size_t)MAX_SEQUENCE_LENGTH ||
        second_length > (size_t)MAX_SEQUENCE_LENGTH) {
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

    result_length = table[first_length * columns + second_length];
    result = malloc(result_length + 1U);

    if (result == NULL) {
        free(table);
        return NULL;
    }

    result[result_length] = '\0';
    position = result_length;
    i = first_length;
    j = second_length;

    while (i > 0U && j > 0U) {
        if (first[i - 1U] == second[j - 1U]) {
            result[--position] = first[i - 1U];
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

    if (position != 0U) {
        free(result);
        return NULL;
    }

    return result;
}

int main(void)
{
    char *first = NULL;
    char *second = NULL;
    char *result;
    size_t first_length = 0U;
    size_t second_length = 0U;
    int status;

    status = read_sequence(&first, &first_length);
    if (status != READ_SUCCESS) {
        if (status == READ_ERROR) {
            fputs("Failed to read the first sequence.\n", stderr);
        } else if (status == READ_MISSING) {
            fputs("The first sequence is missing.\n", stderr);
        } else {
            fputs("The first sequence is too long.\n", stderr);
        }

        return EXIT_FAILURE;
    }

    status = read_sequence(&second, &second_length);
    if (status != READ_SUCCESS) {
        if (status == READ_ERROR) {
            fputs("Failed to read the second sequence.\n", stderr);
        } else if (status == READ_MISSING) {
            fputs("The second sequence is missing.\n", stderr);
        } else {
            fputs("The second sequence is too long.\n", stderr);
        }

        free(first);
        return EXIT_FAILURE;
    }

    result = longest_common_subsequence(first,
                                        first_length,
                                        second,
                                        second_length);

    free(second);
    free(first);

    if (result == NULL) {
        fputs("Unable to compute the longest common subsequence.\n", stderr);
        return EXIT_FAILURE;
    }

    if (fputs(result, stdout) == EOF || fputc('\n', stdout) == EOF) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}