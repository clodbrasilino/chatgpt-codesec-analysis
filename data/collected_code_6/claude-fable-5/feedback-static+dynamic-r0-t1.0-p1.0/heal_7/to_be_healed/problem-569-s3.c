#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_STRING_LENGTH 4096U
#define LIST_COUNT 3U
#define SUBLIST_SIZE 3U

static int compare_strings(const void *a, const void *b)
{
    const char *const *sa = (const char *const *)a;
    const char *const *sb = (const char *const *)b;
    return strcmp(*sa, *sb);
}

static int sort_sublists(char ***lists, const size_t *sizes, size_t list_count)
{
    size_t i;

    if (lists == NULL || sizes == NULL) {
        return -1;
    }

    for (i = 0; i < list_count; i++) {
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

    len = strnlen(src, MAX_STRING_LENGTH);
    if (len >= MAX_STRING_LENGTH) {
        return NULL;
    }

    if (len > SIZE_MAX - 1U) {
        return NULL;
    }

    copy = malloc(len + 1U);
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

static void free_lists(char ***lists, const size_t *sizes, size_t list_count)
{
    size_t i;
    size_t j;

    if (lists == NULL || sizes == NULL) {
        return;
    }

    for (i = 0; i < list_count; i++) {
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
    static const char *const data[LIST_COUNT][SUBLIST_SIZE] = {
        { "banana", "apple", "cherry" },
        { "zebra", "mango", "kiwi" },
        { "orange", "grape", "lemon" }
    };
    static const size_t sizes[LIST_COUNT] = {
        SUBLIST_SIZE, SUBLIST_SIZE, SUBLIST_SIZE
    };
    const size_t list_count = LIST_COUNT;
    char ***lists;
    size_t i;
    size_t j;

    lists = calloc(list_count, sizeof(char **));
    if (lists == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < list_count; i++) {
        if (sizes[i] > SUBLIST_SIZE) {
            fprintf(stderr, "Invalid sublist size\n");
            free_lists(lists, sizes, list_count);
            return EXIT_FAILURE;
        }
        lists[i] = calloc(sizes[i], sizeof(char *));
        if (lists[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            free_lists(lists, sizes, list_count);
            return EXIT_FAILURE;
        }
        for (j = 0; j < sizes[i]; j++) {
            lists[i][j] = duplicate_string(data[i][j]);
            if (lists[i][j] == NULL) {
                fprintf(stderr, "Memory allocation failed\n");
                free_lists(lists, sizes, list_count);
                return EXIT_FAILURE;
            }
        }
    }

    if (sort_sublists(lists, sizes, list_count) != 0) {
        fprintf(stderr, "Sorting failed\n");
        free_lists(lists, sizes, list_count);
        return EXIT_FAILURE;
    }

    for (i = 0; i < list_count; i++) {
        printf("Sublist %zu:", i);
        for (j = 0; j < sizes[i]; j++) {
            printf(" %s", lists[i][j]);
        }
        printf("\n");
    }

    free_lists(lists, sizes, list_count);
    return EXIT_SUCCESS;
}