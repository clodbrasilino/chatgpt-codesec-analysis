#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static int longest_common_subsequence(const char *first,
                                      size_t first_len,
                                      const char *second,
                                      size_t second_len,
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

    sequence[length] = '\0';
    position = length;
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

int main(int argc, char *argv[])
{
    const char *program_name = "lcs";
    char *result = NULL;
    size_t first_len;
    size_t second_len;

    if (argc > 0 && argv != NULL && argv[0] != NULL) {
        program_name = argv[0];
    }

    if (argc != 3 || argv == NULL || argv[1] == NULL || argv[2] == NULL) {
        fprintf(stderr, "Usage: %s <sequence1> <sequence2>\n", program_name);
        return EXIT_FAILURE;
    }

    first_len = strlen(argv[1]);
    second_len = strlen(argv[2]);

    if (longest_common_subsequence(argv[1], first_len,
                                   argv[2], second_len,
                                   &result) != 0) {
        fprintf(stderr, "Failed to compute the longest common subsequence\n");
        return EXIT_FAILURE;
    }

    if (printf("%s\n", result) < 0) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}