#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    int *data;
    size_t len;
} IntList;

static int compare_lists(const void *a, const void *b)
{
    const IntList *la = (const IntList *)a;
    const IntList *lb = (const IntList *)b;
    size_t i;

    if (la->len < lb->len) {
        return -1;
    }
    if (la->len > lb->len) {
        return 1;
    }
    for (i = 0; i < la->len; i++) {
        if (la->data[i] < lb->data[i]) {
            return -1;
        }
        if (la->data[i] > lb->data[i]) {
            return 1;
        }
    }
    return 0;
}

static void sort_list_of_lists(IntList *lists, size_t count)
{
    if (lists == NULL || count == 0) {
        return;
    }
    qsort(lists, count, sizeof(IntList), compare_lists);
}

static int init_list(IntList *list, const int *values, size_t len)
{
    size_t bytes;

    if (list == NULL) {
        return -1;
    }
    list->data = NULL;
    list->len = 0;
    if (len == 0) {
        return 0;
    }
    if (values == NULL) {
        return -1;
    }
    if (len > SIZE_MAX / sizeof(int)) {
        return -1;
    }
    bytes = len * sizeof(int);
    list->data = malloc(bytes);
    if (list->data == NULL) {
        return -1;
    }
    memcpy(list->data, values, bytes);
    list->len = len;
    return 0;
}

static void free_lists(IntList *lists, size_t count)
{
    size_t i;

    if (lists == NULL) {
        return;
    }
    for (i = 0; i < count; i++) {
        free(lists[i].data);
        lists[i].data = NULL;
        lists[i].len = 0;
    }
}

static void print_lists(const IntList *lists, size_t count)
{
    size_t i;
    size_t j;

    if (lists == NULL) {
        return;
    }
    for (i = 0; i < count; i++) {
        printf("[");
        for (j = 0; j < lists[i].len; j++) {
            printf("%d", lists[i].data[j]);
            if (j + 1 < lists[i].len) {
                printf(", ");
            }
        }
        printf("]\n");
    }
}

int main(void)
{
    const int v1[] = {3, 1, 2};
    const int v2[] = {1, 2};
    const int v3[] = {1, 1, 1};
    const int v4[] = {5};
    const int v5[] = {1, 2, 0};
    IntList lists[5];
    size_t count = sizeof(lists) / sizeof(lists[0]);
    size_t i;

    memset(lists, 0, sizeof(lists));

    if (init_list(&lists[0], v1, sizeof(v1) / sizeof(v1[0])) != 0 ||
        init_list(&lists[1], v2, sizeof(v2) / sizeof(v2[0])) != 0 ||
        init_list(&lists[2], v3, sizeof(v3) / sizeof(v3[0])) != 0 ||
        init_list(&lists[3], v4, sizeof(v4) / sizeof(v4[0])) != 0 ||
        init_list(&lists[4], v5, sizeof(v5) / sizeof(v5[0])) != 0) {
        fprintf(stderr, "Memory allocation failed\n");
        free_lists(lists, count);
        return EXIT_FAILURE;
    }

    printf("Before sorting:\n");
    print_lists(lists, count);

    sort_list_of_lists(lists, count);

    printf("After sorting:\n");
    print_lists(lists, count);

    free_lists(lists, count);

    for (i = 0; i < count; i++) {
        if (lists[i].data != NULL) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}