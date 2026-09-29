#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static int bounded_string_length(const char *string, size_t limit, size_t *length)
{
    const char *end;

    if (string == NULL || length == NULL) {
        return -1;
    }

    end = memchr(string, '\0', limit);
    if (end == NULL) {
        return -1;
    }

    *length = (size_t)(end - string);
    return 0;
}

static int longest_common_subsequence(const char *first, const char *second,
                                      size_t maximum_length, char **result)
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

    if (first == NULL || second == NULL || result == NULL ||
        maximum_length == 0U) {
        return -1;
    }

    *result = NULL;

    if (bounded_string_length(first, maximum_length, &first_len) != 0 ||
        bounded_string_length(second, maximum_length, &second_len) != 0) {
        return -1;
    }

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
    sequence[length] = '\0';
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

int main(int argc, char *argv[])
{
    const size_t maximum_argument_length = 1024U * 1024U;
    const char *const *arguments = (const char *const *)argv;
    char *result = NULL;

    if (argc != 3) {
        const char *program_name =
            argc > 0 && arguments != NULL && arguments[0] != NULL
                ? arguments[0]
                : "lcs";

        fprintf(stderr, "Usage: %s <sequence1> <sequence2>\n", program_name);
        return EXIT_FAILURE;
    }

    if (longest_common_subsequence(arguments[1], arguments[2],
                                   maximum_argument_length, &result) != 0) {
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