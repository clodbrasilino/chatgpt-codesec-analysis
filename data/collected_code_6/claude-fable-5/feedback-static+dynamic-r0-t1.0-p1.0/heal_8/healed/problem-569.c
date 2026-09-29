#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_STRING_LEN 4096U
#define LIST_COUNT 3U
#define LIST_SIZE 4U

static int compare_strings(const void *a, const void *b)
{
    const char *const *sa = (const char *const *)a;
    const char *const *sb = (const char *const *)b;
    return strcmp(*sa, *sb);
}

static void sort_sublists(char ***lists, const size_t *sizes, size_t count)
{
    size_t i;

    if (lists == NULL || sizes == NULL) {
        return;
    }

    for (i = 0; i < count; i++) {
        if (lists[i] != NULL && sizes[i] > 1) {
            qsort(lists[i], sizes[i], sizeof(char *), compare_strings);
        }
    }
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

    copy = malloc(len + 1U);
    if (copy == NULL) {
        return NULL;
    }

    memcpy(copy, src, len);
    copy[len] = '\0';
    return copy;
}

static void free_lists(char ***lists, const size_t *sizes, size_t count)
{
    size_t i;
    size_t j;

    if (lists == NULL || sizes == NULL) {
        return;
    }

    for (i = 0; i < count; i++) {
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
    static const char *const data[LIST_COUNT][LIST_SIZE] = {
        { "banana", "apple", "cherry", "date" },
        { "zebra", "yak", "xenon", "walrus" },
        { "delta", "alpha", "charlie", "bravo" }
    };
    static const size_t sizes[LIST_COUNT] = { LIST_SIZE, LIST_SIZE, LIST_SIZE };
    const size_t count = LIST_COUNT;
    char ***lists;
    size_t i;
    size_t j;

    if (count == 0U || count > (SIZE_MAX / sizeof(char **))) {
        fprintf(stderr, "Invalid list count\n");
        return EXIT_FAILURE;
    }

    lists = malloc(count * sizeof(char **));
    if (lists == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; i++) {
        if (sizes[i] == 0U || sizes[i] > LIST_SIZE ||
            sizes[i] > (SIZE_MAX / sizeof(char *))) {
            fprintf(stderr, "Invalid list size\n");
            free_lists(lists, sizes, i);
            return EXIT_FAILURE;
        }
        lists[i] = malloc(sizes[i] * sizeof(char *));
        if (lists[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            free_lists(lists, sizes, i);
            return EXIT_FAILURE;
        }
        for (j = 0; j < sizes[i]; j++) {
            lists[i][j] = duplicate_string(data[i][j]);
            if (lists[i][j] == NULL) {
                size_t k;
                fprintf(stderr, "Memory allocation failed\n");
                for (k = 0; k < j; k++) {
                    free(lists[i][k]);
                }
                free(lists[i]);
                free_lists(lists, sizes, i);
                return EXIT_FAILURE;
            }
        }
    }

    sort_sublists(lists, sizes, count);

    for (i = 0; i < count; i++) {
        printf("Sublist %zu:", i);
        for (j = 0; j < sizes[i]; j++) {
            printf(" %s", lists[i][j]);
        }
        printf("\n");
    }

    free_lists(lists, sizes, count);
    return EXIT_SUCCESS;
}