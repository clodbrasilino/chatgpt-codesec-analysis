#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SEQUENCE_LENGTH 4095U

static int discard_line(void)
{
    int character;

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stdin);
    } while (character != '\n' && character != EOF);

    if (character == EOF && ferror(stdin)) {
        return -1;
    }

    return 0;
}

static int read_sequence(char **sequence)
{
    const size_t capacity = (size_t)MAX_SEQUENCE_LENGTH + 2U;
    char *buffer;
    char *newline;
    size_t length;

    if (sequence == NULL || capacity > (size_t)INT32_MAX) {
        return -1;
    }

    *sequence = NULL;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    if (fgets(buffer, (int)capacity, stdin) == NULL) {
        free(buffer);
        return -1;
    }

    newline = strchr(buffer, '\n');
    if (newline != NULL) {
        *newline = '\0';
        *sequence = buffer;
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    length = strlen(buffer);

    if (length > (size_t)MAX_SEQUENCE_LENGTH) {
        if (discard_line() != 0) {
            free(buffer);
            return -1;
        }

        free(buffer);
        return -2;
    }

    if (feof(stdin)) {
        *sequence = buffer;
        return 0;
    }

    {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int character = fgetc(stdin);

        if (character == EOF) {
            if (ferror(stdin)) {
                free(buffer);
                return -1;
            }
        } else if (character != '\n') {
            if (discard_line() != 0) {
                free(buffer);
                return -1;
            }

            free(buffer);
            return -2;
        }
    }

    *sequence = buffer;
    return 0;
}

static int longest_common_subsequence(const char *first,
                                      const char *second,
                                      char **result)
{
    size_t first_len;
    size_t second_len;
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

    first_len = strnlen(first, (size_t)MAX_SEQUENCE_LENGTH + 1U);
    second_len = strnlen(second, (size_t)MAX_SEQUENCE_LENGTH + 1U);

    if (first_len > (size_t)MAX_SEQUENCE_LENGTH ||
        second_len > (size_t)MAX_SEQUENCE_LENGTH) {
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
            if (position == 0U) {
                free(sequence);
                free(table);
                return -1;
            }

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

    if (position != 0U) {
        free(sequence);
        return -1;
    }

    *result = sequence;
    return 0;
}

int main(void)
{
    char *first = NULL;
    char *second = NULL;
    char *lcs = NULL;
    int status;

    status = read_sequence(&first);
    if (status != 0) {
        fputs(status == -2
                  ? "The first sequence is too long.\n"
                  : "Failed to read the first sequence.\n",
              stderr);
        return EXIT_FAILURE;
    }

    status = read_sequence(&second);
    if (status != 0) {
        fputs(status == -2
                  ? "The second sequence is too long.\n"
                  : "Failed to read the second sequence.\n",
              stderr);
        free(first);
        return EXIT_FAILURE;
    }

    if (longest_common_subsequence(first, second, &lcs) != 0) {
        fputs("Failed to compute the longest common subsequence.\n", stderr);
        free(second);
        free(first);
        return EXIT_FAILURE;
    }

    if (printf("%s\n", lcs) < 0) {
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