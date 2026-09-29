#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MAX_SEQUENCE_LENGTH 4095U

static int read_sequence(char **sequence)
{
    size_t capacity = MAX_SEQUENCE_LENGTH + 2U;
    char *buffer;
    size_t length = 0U;
    int ch;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    while ((ch = fgetc(stdin)) != EOF && ch != '\n') {
        if (ch == '\r') {
            int next = fgetc(stdin);

            if (next != '\n' && next != EOF) {
                ungetc(next, stdin);
            }
            break;
        }

        if (length == MAX_SEQUENCE_LENGTH) {
            while ((ch = fgetc(stdin)) != EOF && ch != '\n') {
            }
            free(buffer);
            return 0;
        }

        buffer[length++] = (char)ch;
    }

    if (ch == EOF && length == 0U && ferror(stdin)) {
        free(buffer);
        return -1;
    }

    if (ch == EOF && length == 0U) {
        free(buffer);
        return 0;
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
    size_t columns;
    size_t rows;
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

    for (i = 1U; i <= first_length; ++i) {
        for (j = 1U; j <= second_length; ++j) {
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
    size_t first_length = 0U;
    size_t second_length = 0U;
    int status;
    int ch;

    status = read_sequence(&first);
    if (status < 0) {
        fputs("Failed to read the first sequence.\n", stderr);
        return EXIT_FAILURE;
    }
    if (status == 0) {
        fputs("The first sequence is missing or too long.\n", stderr);
        return EXIT_FAILURE;
    }

    while (first[first_length] != '\0') {
        ++first_length;
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

    while (second[second_length] != '\0') {
        ++second_length;
    }

    ch = fgetc(stdin);
    if (ch != EOF) {
        ungetc(ch, stdin);
    } else if (ferror(stdin)) {
        fputs("Failed while reading input.\n", stderr);
        free(second);
        free(first);
        return EXIT_FAILURE;
    }

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