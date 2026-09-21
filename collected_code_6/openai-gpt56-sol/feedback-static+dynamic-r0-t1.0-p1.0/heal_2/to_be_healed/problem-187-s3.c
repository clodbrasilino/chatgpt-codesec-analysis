#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_SEQUENCE_LENGTH 4095U

static int read_sequence(char **sequence)
{
    char *buffer;
    size_t capacity = MAX_SEQUENCE_LENGTH + 2U;
    size_t length;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    if (fgets(buffer, (int)capacity, stdin) == NULL) {
        free(buffer);
        return -1;
    }

    length = strcspn(buffer, "\r\n");

    if (buffer[length] == '\0' && length > MAX_SEQUENCE_LENGTH) {
        free(buffer);
        return 1;
    }

    if (buffer[length] == '\0' && !feof(stdin)) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int character = fgetc(stdin);

        if (character != '\n' && character != EOF) {
            while (character != '\n' && character != EOF) {
                /* Possible weaknesses found:
                 * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                character = fgetc(stdin);
            }
            free(buffer);
            return 1;
        }
    }

    buffer[length] = '\0';
    *sequence = buffer;
    return 0;
}

static char *longest_common_subsequence(const char *first,
                                        size_t first_length,
                                        const char *second,
                                        size_t second_length)
{
    size_t columns;
    size_t rows;
    size_t cells;
    size_t *table;
    char *result;
    size_t length;
    size_t position;
    size_t i;
    size_t j;

    if (first == NULL || second == NULL) {
        return NULL;
    }

    if (first_length == SIZE_MAX || second_length == SIZE_MAX) {
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
    return result;
}

int main(void)
{
    char *first = NULL;
    char *second = NULL;
    char *result;
    size_t first_length;
    size_t second_length;
    int status;

    status = read_sequence(&first);
    if (status != 0) {
        fputs(status > 0
                  ? "The first sequence is too long.\n"
                  : "Failed to read the first sequence.\n",
              stderr);
        return EXIT_FAILURE;
    }

    status = read_sequence(&second);
    if (status != 0) {
        fputs(status > 0
                  ? "The second sequence is too long.\n"
                  : "Failed to read the second sequence.\n",
              stderr);
        free(first);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    first_length = strlen(first);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    second_length = strlen(second);

    result = longest_common_subsequence(first, first_length,
                                        second, second_length);
    if (result == NULL) {
        fputs("Unable to compute the longest common subsequence.\n", stderr);
        free(second);
        free(first);
        return EXIT_FAILURE;
    }

    if (fputs(result, stdout) == EOF || fputc('\n', stdout) == EOF) {
        free(result);
        free(second);
        free(first);
        return EXIT_FAILURE;
    }

    free(result);
    free(second);
    free(first);
    return EXIT_SUCCESS;
}