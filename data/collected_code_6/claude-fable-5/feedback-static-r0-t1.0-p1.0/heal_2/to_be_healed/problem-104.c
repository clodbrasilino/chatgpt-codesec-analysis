#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LEN 256U

static int compare_strings(const void *a, const void *b)
{
    const char *const *sa = (const char *const *)a;
    const char *const *sb = (const char *const *)b;
    return strcmp(*sa, *sb);
}

static int sort_sublists(char ***lists, const size_t *sizes, size_t num_lists)
{
    size_t i;

    if (lists == NULL || sizes == NULL) {
        return -1;
    }

    for (i = 0; i < num_lists; i++) {
        if (lists[i] == NULL) {
            return -1;
        }
        if (sizes[i] > 1) {
            qsort(lists[i], sizes[i], sizeof(char *), compare_strings);
        }
    }

    return 0;
}

static char *duplicate_string(const char *src)
{
    size_t len;
    char *copy;

    if (src == NULL) {
        return NULL;
    }

    len = strnlen(src, MAX_STRING_LEN);
    if (len >= MAX_STRING_LEN) {
        return NULL;
    }

    copy = malloc(len + 1);
    if (copy == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(copy, src, len);
    copy[len] = '\0';
    return copy;
}

static void free_lists(char ***lists, const size_t *sizes, size_t num_lists)
{
    size_t i;
    size_t j;

    if (lists == NULL || sizes == NULL) {
        return;
    }

    for (i = 0; i < num_lists; i++) {
        if (lists[i] != NULL) {
            for (j = 0; j < sizes[i]; j++) {
                free(lists[i][j]);
            }
            free(lists[i]);
        }
    }
    free(lists);
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    static const char *const data[3][4] = {
        { "banana", "apple", "cherry", "date" },
        { "zebra", "mango", "kiwi", "lemon" },
        { "orange", "grape", "fig", "plum" }
    };
    const size_t num_lists = 3;
    static const size_t sizes[3] = { 4, 4, 4 };
    char ***lists;
    size_t i;
    size_t j;

    lists = calloc(num_lists, sizeof(char **));
    if (lists == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < num_lists; i++) {
        lists[i] = calloc(sizes[i], sizeof(char *));
        if (lists[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            free_lists(lists, sizes, num_lists);
            return EXIT_FAILURE;
        }
        for (j = 0; j < sizes[i]; j++) {
            lists[i][j] = duplicate_string(data[i][j]);
            if (lists[i][j] == NULL) {
                fprintf(stderr, "Memory allocation failed\n");
                free_lists(lists, sizes, num_lists);
                return EXIT_FAILURE;
            }
        }
    }

    if (sort_sublists(lists, sizes, num_lists) != 0) {
        fprintf(stderr, "Sorting failed\n");
        free_lists(lists, sizes, num_lists);
        return EXIT_FAILURE;
    }

    for (i = 0; i < num_lists; i++) {
        printf("List %zu:", i);
        for (j = 0; j < sizes[i]; j++) {
            printf(" %s", lists[i][j]);
        }
        printf("\n");
    }

    free_lists(lists, sizes, num_lists);
    return EXIT_SUCCESS;
}