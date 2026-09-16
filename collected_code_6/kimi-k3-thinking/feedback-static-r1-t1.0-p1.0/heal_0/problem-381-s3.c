#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    int *data;
    size_t size;
} IntList;

static int compare_lists(const IntList *a, const IntList *b, size_t index)
{
    int va = 0;
    int vb = 0;

    if (a != NULL && a->data != NULL && index < a->size) {
        va = a->data[index];
    }
    if (b != NULL && b->data != NULL && index < b->size) {
        vb = b->data[index];
    }
    if (va < vb) {
        return -1;
    }
    if (va > vb) {
        return 1;
    }
    return 0;
}

static void merge_ranges(IntList *lists, IntList *tmp, size_t left, size_t mid, size_t right, size_t index)
{
    size_t i = left;
    size_t j = mid;
    size_t k = left;

    while (i < mid && j < right) {
        if (compare_lists(&lists[i], &lists[j], index) <= 0) {
            tmp[k] = lists[i];
            i++;
        } else {
            tmp[k] = lists[j];
            j++;
        }
        k++;
    }
    while (i < mid) {
        tmp[k] = lists[i];
        i++;
        k++;
    }
    while (j < right) {
        tmp[k] = lists[j];
        j++;
        k++;
    }
    for (i = left; i < right; i++) {
        lists[i] = tmp[i];
    }
}

static void merge_sort_recursive(IntList *lists, IntList *tmp, size_t left, size_t right, size_t index)
{
    size_t mid;

    if (right <= left || right - left < 2U) {
        return;
    }
    mid = left + (right - left) / 2U;
    merge_sort_recursive(lists, tmp, left, mid, index);
    merge_sort_recursive(lists, tmp, mid, right, index);
    merge_ranges(lists, tmp, left, mid, right, index);
}

int sort_lists_by_index(IntList *lists, size_t count, size_t index)
{
    IntList *tmp = NULL;

    if (lists == NULL) {
        if (count == 0U) {
            return 0;
        }
        return -1;
    }
    if (count < 2U) {
        return 0;
    }
    if (count > SIZE_MAX / sizeof(IntList)) {
        return -1;
    }
    tmp = (IntList *)malloc(count * sizeof(IntList));
    if (tmp == NULL) {
        return -1;
    }
    merge_sort_recursive(lists, tmp, 0U, count, index);
    free(tmp);
    return 0;
}

static int build_lists(IntList **out_lists, size_t *out_count)
{
    static const int values[4][3] = {
        {3, 30, 300},
        {1, 10, 100},
        {4, 40, 400},
        {2, 20, 200}
    };
    const size_t count = 4U;
    const size_t width = 3U;
    IntList *lists = NULL;
    size_t i;
    size_t j;
    size_t k;

    if (out_lists == NULL || out_count == NULL) {
        return -1;
    }
    lists = (IntList *)calloc(count, sizeof(IntList));
    if (lists == NULL) {
        return -1;
    }
    for (i = 0U; i < count; i++) {
        lists[i].data = (int *)malloc(width * sizeof(int));
        if (lists[i].data == NULL) {
            for (k = 0U; k < i; k++) {
                free(lists[k].data);
                lists[k].data = NULL;
                lists[k].size = 0U;
            }
            free(lists);
            return -1;
        }
        lists[i].size = width;
        for (j = 0U; j < width; j++) {
            lists[i].data[j] = values[i][j];
        }
    }
    *out_lists = lists;
    *out_count = count;
    return 0;
}

static void print_lists(const IntList *lists, size_t count)
{
    size_t i;
    size_t j;

    if (lists == NULL) {
        return;
    }
    for (i = 0U; i < count; i++) {
        (void)printf("[");
        for (j = 0U; j < lists[i].size; j++) {
            (void)printf("%d", lists[i].data[j]);
            if (j + 1U < lists[i].size) {
                (void)printf(", ");
            }
        }
        (void)printf("]\n");
    }
}

static void destroy_lists(IntList *lists, size_t count)
{
    size_t i;

    if (lists == NULL) {
        return;
    }
    for (i = 0U; i < count; i++) {
        free(lists[i].data);
        lists[i].data = NULL;
        lists[i].size = 0U;
    }
    free(lists);
}

int main(void)
{
    IntList *lists = NULL;
    size_t count = 0U;
    const size_t sort_index = 1U;

    if (build_lists(&lists, &count) != 0) {
        (void)fprintf(stderr, "error: failed to build lists\n");
        return EXIT_FAILURE;
    }

    (void)printf("Before sorting:\n");
    print_lists(lists, count);

    if (sort_lists_by_index(lists, count, sort_index) != 0) {
        (void)fprintf(stderr, "error: failed to sort lists\n");
        destroy_lists(lists, count);
        lists = NULL;
        return EXIT_FAILURE;
    }

    (void)printf("After sorting by inner index %zu:\n", sort_index);
    print_lists(lists, count);

    destroy_lists(lists, count);
    lists = NULL;

    return EXIT_SUCCESS;
}