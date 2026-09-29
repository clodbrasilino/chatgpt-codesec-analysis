#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *data;
    size_t length;
} IntList;

static int compare_lists(const void *a, const void *b)
{
    const IntList *list_a = *(const IntList **)a;
    const IntList *list_b = *(const IntList **)b;
    size_t min_length;
    size_t i;

    if (list_a->length < list_b->length) {
        return -1;
    }
    if (list_a->length > list_b->length) {
        return 1;
    }

    min_length = list_a->length;
    for (i = 0; i < min_length; ++i) {
        if (list_a->data[i] < list_b->data[i]) {
            return -1;
        }
        if (list_a->data[i] > list_b->data[i]) {
            return 1;
        }
    }

    return 0;
}

void sort_list_of_lists(IntList **lists, size_t count)
{
    if (lists == NULL || count == 0) {
        return;
    }
    qsort(lists, count, sizeof(IntList *), compare_lists);
}

static IntList *create_list(const int *values, size_t length)
{
    IntList *list;
    size_t i;

    list = malloc(sizeof(IntList));
    if (list == NULL) {
        return NULL;
    }

    list->data = malloc(length * sizeof(int));
    if (list->data == NULL) {
        free(list);
        return NULL;
    }

    list->length = length;
    for (i = 0; i < length; ++i) {
        list->data[i] = values[i];
    }

    return list;
}

static void free_list(IntList *list)
{
    if (list != NULL) {
        free(list->data);
        free(list);
    }
}

static void print_lists(IntList **lists, size_t count)
{
    size_t i;
    size_t j;

    for (i = 0; i < count; ++i) {
        printf("[");
        for (j = 0; j < lists[i]->length; ++j) {
            printf("%d", lists[i]->data[j]);
            if (j < lists[i]->length - 1) {
                printf(", ");
            }
        }
        printf("]\n");
    }
}

int main(void)
{
    const int values_1[] = {3, 1, 2};
    const int values_2[] = {1, 2};
    const int values_3[] = {1, 2, 3};
    const int values_4[] = {2};
    const int values_5[] = {1, 2};
    IntList **lists;
    size_t count = 5;
    size_t i;
    int result = EXIT_SUCCESS;

    lists = malloc(count * sizeof(IntList *));
    if (lists == NULL) {
        return EXIT_FAILURE;
    }

    lists[0] = create_list(values_1, 3);
    lists[1] = create_list(values_2, 2);
    lists[2] = create_list(values_3, 3);
    lists[3] = create_list(values_4, 1);
    lists[4] = create_list(values_5, 2);

    for (i = 0; i < count; ++i) {
        if (lists[i] == NULL) {
            result = EXIT_FAILURE;
            goto cleanup;
        }
    }

    printf("Before sorting:\n");
    print_lists(lists, count);

    sort_list_of_lists(lists, count);

    printf("\nAfter sorting:\n");
    print_lists(lists, count);

cleanup:
    for (i = 0; i < count; ++i) {
        free_list(lists[i]);
    }
    free(lists);

    return result;
}