#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t length;
} IntList;

static int compare_lists(const void *a, const void *b)
{
    const IntList *la = (const IntList *)a;
    const IntList *lb = (const IntList *)b;
    size_t i;

    if (la->length < lb->length) {
        return -1;
    }
    if (la->length > lb->length) {
        return 1;
    }
    for (i = 0; i < la->length; i++) {
        if (la->data[i] < lb->data[i]) {
            return -1;
        }
        if (la->data[i] > lb->data[i]) {
            return 1;
        }
    }
    return 0;
}

static int sort_list_of_lists(IntList *lists, size_t count)
{
    if (lists == NULL && count > 0) {
        return -1;
    }
    if (count > 1) {
        qsort(lists, count, sizeof(IntList), compare_lists);
    }
    return 0;
}

static IntList *create_list(const int *values, size_t length)
{
    IntList *list;
    size_t i;

    list = malloc(sizeof(IntList));
    if (list == NULL) {
        return NULL;
    }
    if (length > 0) {
        list->data = malloc(length * sizeof(int));
        if (list->data == NULL) {
            free(list);
            return NULL;
        }
        for (i = 0; i < length; i++) {
            list->data[i] = values[i];
        }
    } else {
        list->data = NULL;
    }
    list->length = length;
    return list;
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
        lists[i].length = 0;
    }
    free(lists);
}

static void print_lists(const IntList *lists, size_t count)
{
    size_t i;
    size_t j;

    for (i = 0; i < count; i++) {
        printf("[");
        for (j = 0; j < lists[i].length; j++) {
            if (j > 0) {
                printf(", ");
            }
            printf("%d", lists[i].data[j]);
        }
        printf("]\n");
    }
}

int main(void)
{
    static const int v1[] = {3, 1, 2};
    static const int v2[] = {5, 4};
    static const int v3[] = {1, 2, 3};
    static const int v4[] = {9};
    static const int v5[] = {5, 3};
    const size_t count = 5;
    IntList *lists;
    IntList *tmp;
    size_t i;

    lists = malloc(count * sizeof(IntList));
    if (lists == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    for (i = 0; i < count; i++) {
        lists[i].data = NULL;
        lists[i].length = 0;
    }

    tmp = create_list(v1, sizeof(v1) / sizeof(v1[0]));
    if (tmp == NULL) {
        free_lists(lists, count);
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    lists[0] = *tmp;
    free(tmp);

    tmp = create_list(v2, sizeof(v2) / sizeof(v2[0]));
    if (tmp == NULL) {
        free_lists(lists, count);
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    lists[1] = *tmp;
    free(tmp);

    tmp = create_list(v3, sizeof(v3) / sizeof(v3[0]));
    if (tmp == NULL) {
        free_lists(lists, count);
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    lists[2] = *tmp;
    free(tmp);

    tmp = create_list(v4, sizeof(v4) / sizeof(v4[0]));
    if (tmp == NULL) {
        free_lists(lists, count);
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    lists[3] = *tmp;
    free(tmp);

    tmp = create_list(v5, sizeof(v5) / sizeof(v5[0]));
    if (tmp == NULL) {
        free_lists(lists, count);
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    lists[4] = *tmp;
    free(tmp);

    printf("Before sorting:\n");
    print_lists(lists, count);

    if (sort_list_of_lists(lists, count) != 0) {
        free_lists(lists, count);
        fprintf(stderr, "Sorting failed\n");
        return EXIT_FAILURE;
    }

    printf("After sorting:\n");
    print_lists(lists, count);

    free_lists(lists, count);
    return EXIT_SUCCESS;
}