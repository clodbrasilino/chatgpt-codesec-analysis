#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 100

struct entry {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[MAX_LEN];
    int count;
};

static const char *second_most_frequent(const char *arr[], size_t n,
                                        struct entry *table, size_t *table_size)
{
    size_t i;
    size_t j;
    size_t unique = 0;
    size_t first_idx;
    size_t second_idx;
    int found_second = 0;

    if (arr == NULL || table == NULL || table_size == NULL || n == 0) {
        return NULL;
    }

    for (i = 0; i < n; i++) {
        int found = 0;
        size_t len;

        if (arr[i] == NULL) {
            return NULL;
        }

        len = strnlen(arr[i], MAX_LEN);
        if (len >= MAX_LEN) {
            return NULL;
        }

        for (j = 0; j < unique; j++) {
            if (strncmp(table[j].str, arr[i], MAX_LEN) == 0) {
                table[j].count++;
                found = 1;
                break;
            }
        }

        if (found == 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(table[unique].str, arr[i], len);
            table[unique].str[len] = '\0';
            table[unique].count = 1;
            unique++;
        }
    }

    *table_size = unique;

    if (unique < 2) {
        return NULL;
    }

    first_idx = 0;
    second_idx = 0;

    for (i = 1; i < unique; i++) {
        if (table[i].count > table[first_idx].count) {
            first_idx = i;
        }
    }

    for (i = 0; i < unique; i++) {
        if (i == first_idx) {
            continue;
        }
        if (found_second == 0 || table[i].count > table[second_idx].count) {
            second_idx = i;
            found_second = 1;
        }
    }

    if (found_second == 0) {
        return NULL;
    }

    return table[second_idx].str;
}

int main(void)
{
    const char *sequence[] = {
        "apple", "banana", "apple", "orange",
        "banana", "apple", "orange", "banana", "banana"
    };
    size_t n = sizeof(sequence) / sizeof(sequence[0]);
    struct entry *table;
    size_t table_size = 0;
    const char *result;

    table = calloc(n, sizeof(struct entry));
    if (table == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    result = second_most_frequent(sequence, n, table, &table_size);

    if (result == NULL) {
        fprintf(stderr, "No second most frequent string found\n");
        free(table);
        return EXIT_FAILURE;
    }

    if (printf("Second most frequent string: %s\n", result) < 0) {
        free(table);
        return EXIT_FAILURE;
    }

    free(table);
    return EXIT_SUCCESS;
}