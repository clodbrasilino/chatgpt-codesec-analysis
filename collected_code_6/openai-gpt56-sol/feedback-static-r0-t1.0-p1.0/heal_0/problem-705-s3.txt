#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *values;
    size_t length;
} IntList;

static int compare_ints(const void *lhs, const void *rhs)
{
    const int a = *(const int *)lhs;
    const int b = *(const int *)rhs;

    return (a > b) - (a < b);
}

static int compare_lists(const void *lhs, const void *rhs)
{
    const IntList *a = lhs;
    const IntList *b = rhs;
    size_t i;

    if (a->length != b->length) {
        return (a->length > b->length) - (a->length < b->length);
    }

    for (i = 0; i < a->length; ++i) {
        if (a->values[i] != b->values[i]) {
            return (a->values[i] > b->values[i]) -
                   (a->values[i] < b->values[i]);
        }
    }

    return 0;
}

static int sort_list_of_lists(IntList *lists, size_t count)
{
    size_t i;

    if (count > 0 && lists == NULL) {
        return -1;
    }

    for (i = 0; i < count; ++i) {
        if (lists[i].length > 0 && lists[i].values == NULL) {
            return -1;
        }

        if (lists[i].length > 1) {
            qsort(lists[i].values, lists[i].length,
                  sizeof(*lists[i].values), compare_ints);
        }
    }

    if (count > 1) {
        qsort(lists, count, sizeof(*lists), compare_lists);
    }

    return 0;
}

static void free_lists(IntList *lists, size_t count)
{
    size_t i;

    if (lists == NULL) {
        return;
    }

    for (i = 0; i < count; ++i) {
        free(lists[i].values);
    }

    free(lists);
}

static int read_lists(IntList **result, size_t *result_count)
{
    IntList *lists = NULL;
    size_t count;
    size_t i;

    if (result == NULL || result_count == NULL) {
        return -1;
    }

    *result = NULL;
    *result_count = 0;

    if (scanf("%zu", &count) != 1) {
        return -1;
    }

    if (count > SIZE_MAX / sizeof(*lists)) {
        return -1;
    }

    if (count > 0) {
        lists = calloc(count, sizeof(*lists));
        if (lists == NULL) {
            return -1;
        }
    }

    for (i = 0; i < count; ++i) {
        size_t j;

        if (scanf("%zu", &lists[i].length) != 1) {
            free_lists(lists, count);
            return -1;
        }

        if (lists[i].length > SIZE_MAX / sizeof(*lists[i].values)) {
            free_lists(lists, count);
            return -1;
        }

        if (lists[i].length > 0) {
            lists[i].values = malloc(lists[i].length *
                                     sizeof(*lists[i].values));
            if (lists[i].values == NULL) {
                free_lists(lists, count);
                return -1;
            }
        }

        for (j = 0; j < lists[i].length; ++j) {
            if (scanf("%d", &lists[i].values[j]) != 1) {
                free_lists(lists, count);
                return -1;
            }
        }
    }

    *result = lists;
    *result_count = count;
    return 0;
}

static int print_lists(const IntList *lists, size_t count)
{
    size_t i;

    if (count > 0 && lists == NULL) {
        return -1;
    }

    for (i = 0; i < count; ++i) {
        size_t j;

        if (printf("%zu", lists[i].length) < 0) {
            return -1;
        }

        for (j = 0; j < lists[i].length; ++j) {
            if (printf(" %d", lists[i].values[j]) < 0) {
                return -1;
            }
        }

        if (putchar('\n') == EOF) {
            return -1;
        }
    }

    return 0;
}

int main(void)
{
    IntList *lists = NULL;
    size_t count = 0;
    int status = EXIT_FAILURE;

    if (read_lists(&lists, &count) != 0) {
        fputs("Invalid input or allocation failure.\n", stderr);
        goto cleanup;
    }

    if (sort_list_of_lists(lists, count) != 0) {
        fputs("Unable to sort lists.\n", stderr);
        goto cleanup;
    }

    if (print_lists(lists, count) != 0) {
        fputs("Output failure.\n", stderr);
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free_lists(lists, count);
    return status;
}