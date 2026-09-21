#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static int longest_common_subsequence(const char *first, const char *second,
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

    if (first == NULL || second == NULL || result == NULL) {
        return -1;
    }

    *result = NULL;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    first_len = strlen(first);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    second_len = strlen(second);

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

    sequence[length] = '\0';
    i = first_len;
    j = second_len;

    while (i > 0U && j > 0U) {
        if (first[i - 1U] == second[j - 1U]) {
            sequence[--length] = first[i - 1U];
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char first[4096];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char second[4096];
    char *lcs;

    if (fgets(first, sizeof(first), stdin) == NULL) {
        fputs("Failed to read the first sequence.\n", stderr);
        return EXIT_FAILURE;
    }

    if (strchr(first, '\n') == NULL && !feof(stdin)) {
        fputs("The first sequence is too long.\n", stderr);
        return EXIT_FAILURE;
    }

    first[strcspn(first, "\n")] = '\0';

    if (fgets(second, sizeof(second), stdin) == NULL) {
        fputs("Failed to read the second sequence.\n", stderr);
        return EXIT_FAILURE;
    }

    if (strchr(second, '\n') == NULL && !feof(stdin)) {
        fputs("The second sequence is too long.\n", stderr);
        return EXIT_FAILURE;
    }

    second[strcspn(second, "\n")] = '\0';

    if (longest_common_subsequence(first, second, &lcs) != 0) {
        fputs("Failed to compute the longest common subsequence.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%s\n", lcs) < 0) {
        free(lcs);
        return EXIT_FAILURE;
    }

    free(lcs);
    return EXIT_SUCCESS;
}