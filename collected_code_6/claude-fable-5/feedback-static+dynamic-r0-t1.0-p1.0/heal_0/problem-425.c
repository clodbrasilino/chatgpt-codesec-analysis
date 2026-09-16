#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *items;
    size_t length;
} SubList;

typedef struct {
    SubList *sublists;
    size_t count;
} ListOfLists;

static int sublist_contains(const SubList *sub, int element)
{
    size_t i;

    if (sub == NULL || sub->items == NULL) {
        return 0;
    }

    for (i = 0; i < sub->length; i++) {
        if (sub->items[i] == element) {
            return 1;
        }
    }

    return 0;
}

size_t count_sublists_with_element(const ListOfLists *list, int element)
{
    size_t i;
    size_t count = 0;

    if (list == NULL || list->sublists == NULL) {
        return 0;
    }

    for (i = 0; i < list->count; i++) {
        if (sublist_contains(&list->sublists[i], element)) {
            count++;
        }
    }

    return count;
}

static int init_sublist(SubList *sub, const int *values, size_t length)
{
    size_t i;

    if (sub == NULL || values == NULL || length == 0) {
        return -1;
    }

    sub->items = malloc(length * sizeof(int));
    if (sub->items == NULL) {
        return -1;
    }

    for (i = 0; i < length; i++) {
        sub->items[i] = values[i];
    }
    sub->length = length;

    return 0;
}

static void free_list(ListOfLists *list)
{
    size_t i;

    if (list == NULL || list->sublists == NULL) {
        return;
    }

    for (i = 0; i < list->count; i++) {
        free(list->sublists[i].items);
        list->sublists[i].items = NULL;
        list->sublists[i].length = 0;
    }

    free(list->sublists);
    list->sublists = NULL;
    list->count = 0;
}

int main(void)
{
    ListOfLists list;
    size_t result;
    int target = 3;
    const int data0[] = {1, 3};
    const int data1[] = {5, 7};
    const int data2[] = {1, 3};
    const int data3[] = {13, 15, 17};
    const size_t num_sublists = 4;

    list.sublists = malloc(num_sublists * sizeof(SubList));
    if (list.sublists == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    list.count = num_sublists;

    {
        size_t i;
        for (i = 0; i < num_sublists; i++) {
            list.sublists[i].items = NULL;
            list.sublists[i].length = 0;
        }
    }

    if (init_sublist(&list.sublists[0], data0, 2) != 0 ||
        init_sublist(&list.sublists[1], data1, 2) != 0 ||
        init_sublist(&list.sublists[2], data2, 2) != 0 ||
        init_sublist(&list.sublists[3], data3, 3) != 0) {
        fprintf(stderr, "Failed to initialize sublists\n");
        free_list(&list);
        return EXIT_FAILURE;
    }

    result = count_sublists_with_element(&list, target);
    printf("Number of sublists containing %d: %zu\n", target, result);

    free_list(&list);

    return EXIT_SUCCESS;
}