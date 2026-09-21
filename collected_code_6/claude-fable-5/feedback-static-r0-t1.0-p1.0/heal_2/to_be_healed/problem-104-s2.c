#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LEN 4096

static int compare_strings(const void *a, const void *b)
{
    const char *const *sa = (const char *const *)a;
    const char *const *sb = (const char *const *)b;
    return strcmp(*sa, *sb);
}

static void sort_sublists(char ***lists, const size_t *sizes, size_t list_count)
{
    size_t i;

    if (lists == NULL || sizes == NULL) {
        return;
    }

    for (i = 0; i < list_count; i++) {
        if (lists[i] != NULL && sizes[i] > 1) {
            qsort(lists[i], sizes[i], sizeof(char *), compare_strings);
        }
    }
}

static size_t bounded_strlen(const char *src, size_t max_len)
{
    size_t len = 0;

    while (len < max_len && src[len] != '\0') {
        len++;
    }
    return len;
}

static char *duplicate_string(const char *src)
{
    size_t len;
    char *copy;

    if (src == NULL) {
        return NULL;
    }

    len = bounded_strlen(src, MAX_STRING_LEN);
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
    const char *data0[] = { "banana", "apple", "cherry" };
    const char *data1[] = { "delta", "alpha", "charlie", "bravo" };
    const char *data2[] = { "zebra", "yak" };
    const char *const *source[] = { data0, data1, data2 };
    const size_t sizes[] = { 3, 4, 2 };
    const size_t list_count = 3;
    char ***lists;
    size_t i;
    size_t j;

    lists = calloc(list_count, sizeof(char **));
    if (lists == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < list_count; i++) {
        lists[i] = calloc(sizes[i], sizeof(char *));
        if (lists[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            free_lists(lists, sizes, list_count);
            return EXIT_FAILURE;
        }
        for (j = 0; j < sizes[i]; j++) {
            lists[i][j] = duplicate_string(source[i][j]);
            if (lists[i][j] == NULL) {
                fprintf(stderr, "Memory allocation failed\n");
                free_lists(lists, sizes, list_count);
                return EXIT_FAILURE;
            }
        }
    }

    sort_sublists(lists, sizes, list_count);

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