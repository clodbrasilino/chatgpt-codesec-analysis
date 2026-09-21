#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define MAX_SEQUENCE_LENGTH 4095U

static int discard_line(void)
{
    int ch;

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    } while (ch != '\n' && ch != EOF);

    return ch == EOF && ferror(stdin) ? -1 : 0;
}

static int read_sequence(char **sequence)
{
    char *buffer;
    size_t length;
    /* Possible weaknesses found:
     *  The scope of the variable 'ch' can be reduced. [variableScope]
     */
    int ch;

    if (sequence == NULL) {
        return -1;
    }

    *sequence = NULL;
    buffer = malloc(MAX_SEQUENCE_LENGTH + 1U);
    if (buffer == NULL) {
        return -1;
    }

    length = 0U;

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);

        if (ch == EOF) {
            if (ferror(stdin)) {
                free(buffer);
                return -1;
            }

            if (length == 0U) {
                free(buffer);
                return 0;
            }

            break;
        }

        if (ch == '\n') {
            break;
        }

        if (ch == '\r') {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            int next = fgetc(stdin);

            if (next == EOF) {
                if (ferror(stdin)) {
                    free(buffer);
                    return -1;
                }
            } else if (next != '\n' && ungetc(next, stdin) == EOF) {
                free(buffer);
                return -1;
            }

            break;
        }

        if (length >= MAX_SEQUENCE_LENGTH) {
            int discard_status = discard_line();

            free(buffer);
            return discard_status < 0 ? -1 : 0;
        }

        buffer[length++] = (char)ch;
    }

    buffer[length] = '\0';
    *sequence = buffer;
    return 1;
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
    size_t i;
    size_t j;
    size_t position;

    if (first == NULL || second == NULL) {
        return NULL;
    }

    if (first_length == SIZE_MAX || second_length == SIZE_MAX) {
        return NULL;
    }

    rows = first_length + 1U;
    /* Possible weaknesses found:
     *  Assignment 'columns=second_length+1U', assigned value is greater than 0
     */
    columns = second_length + 1U;

    /* Possible weaknesses found:
     *  Condition 'columns!=0U' is always true [knownConditionTrueFalse]
     *  Condition 'columns!=0U' is always true
     */
    if (columns != 0U && rows > SIZE_MAX / columns) {
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

    for (i = 1U; i <= first_length; ++i) {
        for (j = 1U; j <= second_length; ++j) {
            size_t index = i * columns + j;

            if (first[i - 1U] == second[j - 1U]) {
                table[index] =
                    table[(i - 1U) * columns + j - 1U] + 1U;
            } else {
                size_t above = table[(i - 1U) * columns + j];
                size_t left = table[i * columns + j - 1U];

                table[index] = above >= left ? above : left;
            }
        }
    }

    position = table[first_length * columns + second_length];

    if (position == SIZE_MAX) {
        free(table);
        return NULL;
    }

    result = malloc(position + 1U);
    if (result == NULL) {
        free(table);
        return NULL;
    }

    result[position] = '\0';
    i = first_length;
    j = second_length;

    while (i > 0U && j > 0U) {
        if (first[i - 1U] == second[j - 1U]) {
            result[--position] = first[i - 1U];
            --i;
            --j;
        } else if (table[(i - 1U) * columns + j] >=
                   table[i * columns + j - 1U]) {
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
    if (status < 0) {
        fputs("Failed to read the first sequence.\n", stderr);
        return EXIT_FAILURE;
    }

    if (status == 0) {
        fputs("The first sequence is missing or too long.\n", stderr);
        return EXIT_FAILURE;
    }

    status = read_sequence(&second);
    if (status < 0) {
        fputs("Failed to read the second sequence.\n", stderr);
        free(first);
        return EXIT_FAILURE;
    }

    if (status == 0) {
        fputs("The second sequence is missing or too long.\n", stderr);
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