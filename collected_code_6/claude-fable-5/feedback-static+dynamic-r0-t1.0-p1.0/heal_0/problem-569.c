#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    len = strlen(src) + 1;
    copy = malloc(len);
    if (copy == NULL) {
        return NULL;
    }
    memcpy(copy, src, len);
    return copy;
}

static void free_lists(char ***lists, const size_t *sizes, size_t count)
{
    size_t i;
    size_t j;

    if (lists == NULL) {
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
    static const char *data[3][4] = {
        { "banana", "apple", "cherry", "date" },
        { "zebra", "yak", "xenon", "walrus" },
        { "delta", "alpha", "charlie", "bravo" }
    };
    size_t sizes[3] = { 4, 4, 4 };
    size_t count = 3;
    char ***lists;
    size_t i;
    size_t j;

    lists = malloc(count * sizeof(char **));
    if (lists == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; i++) {
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