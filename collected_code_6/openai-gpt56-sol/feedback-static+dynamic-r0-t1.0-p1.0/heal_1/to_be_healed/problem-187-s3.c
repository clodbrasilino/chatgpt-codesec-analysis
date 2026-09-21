#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static char *longest_common_subsequence(const char *first, const char *second)
{
    size_t first_length;
    size_t second_length;
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

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    first_length = strlen(first);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    second_length = strlen(second);

    if (second_length == SIZE_MAX) {
        return NULL;
    }

    columns = second_length + 1U;

    if (first_length == SIZE_MAX || first_length + 1U > SIZE_MAX / columns) {
        return NULL;
    }

    cells = (first_length + 1U) * columns;

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
                table[index] = table[(i - 1U) * columns + (j - 1U)] + 1U;
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char first[4096];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char second[4096];
    char *result;

    if (fgets(first, sizeof(first), stdin) == NULL) {
        fputs("Failed to read the first sequence.\n", stderr);
        return EXIT_FAILURE;
    }

    if (strchr(first, '\n') == NULL && !feof(stdin)) {
        fputs("The first sequence is too long.\n", stderr);
        return EXIT_FAILURE;
    }

    first[strcspn(first, "\r\n")] = '\0';

    if (fgets(second, sizeof(second), stdin) == NULL) {
        fputs("Failed to read the second sequence.\n", stderr);
        return EXIT_FAILURE;
    }

    if (strchr(second, '\n') == NULL && !feof(stdin)) {
        fputs("The second sequence is too long.\n", stderr);
        return EXIT_FAILURE;
    }

    second[strcspn(second, "\r\n")] = '\0';

    result = longest_common_subsequence(first, second);
    if (result == NULL) {
        fputs("Unable to compute the longest common subsequence.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%s\n", result) < 0) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}