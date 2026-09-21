#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_SEQUENCE_LENGTH 4095U

static int read_sequence(FILE *stream, char **sequence)
{
    char *buffer;
    size_t capacity = 128U;
    size_t length = 0U;
    int ch;

    if (stream == NULL || sequence == NULL) {
        return -1;
    }

    *sequence = NULL;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stream)) != '\n' && ch != EOF) {
        char *resized;
        /* Possible weaknesses found:
         *  The scope of the variable 'new_capacity' can be reduced. [variableScope]
         */
        size_t new_capacity;

        if (length >= MAX_SEQUENCE_LENGTH) {
            while (ch != '\n' && ch != EOF) {
                /* Possible weaknesses found:
                 * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                ch = fgetc(stream);
            }
            free(buffer);
            return 1;
        }

        if (length + 1U >= capacity) {
            if (capacity > (MAX_SEQUENCE_LENGTH + 1U) / 2U) {
                new_capacity = MAX_SEQUENCE_LENGTH + 1U;
            } else {
                new_capacity = capacity * 2U;
            }

            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return -1;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    if (ch == EOF && ferror(stream)) {
        free(buffer);
        return -1;
    }

    if (ch == EOF && length == 0U) {
        free(buffer);
        return 2;
    }

    buffer[length] = '\0';
    *sequence = buffer;
    return 0;
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
    size_t i;
    size_t j;
    size_t length;
    size_t position;

    if (first == NULL || second == NULL || result == NULL) {
        return -1;
    }

    *result = NULL;

    if (first_len == SIZE_MAX || second_len == SIZE_MAX) {
        return -1;
    }

    rows = first_len + 1U;
    /* Possible weaknesses found:
     *  Assignment 'columns=second_len+1U', assigned value is greater than 0
     */
    columns = second_len + 1U;

    /* Possible weaknesses found:
     *  Condition 'columns!=0U' is always true
     *  Condition 'columns!=0U' is always true [knownConditionTrueFalse]
     */
    if (columns != 0U && rows > SIZE_MAX / columns) {
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

    if (length == SIZE_MAX) {
        free(table);
        return -1;
    }

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
    size_t first_len;
    size_t second_len;
    int status;

    status = read_sequence(stdin, &first);
    if (status != 0) {
        if (status == 1) {
            fputs("The first sequence is too long.\n", stderr);
        } else {
            fputs("Failed to read the first sequence.\n", stderr);
        }
        return EXIT_FAILURE;
    }

    status = read_sequence(stdin, &second);
    if (status != 0) {
        if (status == 1) {
            fputs("The second sequence is too long.\n", stderr);
        } else {
            fputs("Failed to read the second sequence.\n", stderr);
        }
        free(first);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    first_len = strlen(first);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    second_len = strlen(second);

    if (longest_common_subsequence(first, first_len, second, second_len,
                                   &lcs) != 0) {
        fputs("Failed to compute the longest common subsequence.\n", stderr);
        free(second);
        free(first);
        return EXIT_FAILURE;
    }

    if (fputs(lcs, stdout) == EOF || fputc('\n', stdout) == EOF) {
        free(lcs);
        free(second);
        free(first);
        return EXIT_FAILURE;
    }

    free(lcs);
    free(second);
    free(first);
    return EXIT_SUCCESS;
}