#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *data;
    size_t size;
} IntList;

typedef struct {
    IntList *lists;
    size_t count;
} ListOfLists;

static int init_list(IntList *list, const int *values, size_t size)
{
    if (list == NULL) {
        return -1;
    }
    list->data = NULL;
    list->size = 0;
    if (size == 0) {
        return 0;
    }
    if (values == NULL) {
        return -1;
    }
    list->data = malloc(size * sizeof(*list->data));
    if (list->data == NULL) {
        return -1;
    }
    memcpy(list->data, values, size * sizeof(*list->data));
    list->size = size;
    return 0;
}

static void free_list(IntList *list)
{
    if (list == NULL) {
        return;
    }
    free(list->data);
    list->data = NULL;
    list->size = 0;
}

static void free_list_of_lists(ListOfLists *collection)
{
    size_t i;

    if (collection == NULL) {
        return;
    }
    if (collection->lists != NULL) {
        for (i = 0; i < collection->count; i++) {
            free_list(&collection->lists[i]);
        }
        free(collection->lists);
    }
    collection->lists = NULL;
    collection->count = 0;
}

static int lists_equal(const IntList *first, const IntList *second)
{
    if (first == NULL || second == NULL) {
        return 0;
    }
    if (first->size != second->size) {
        return 0;
    }
    if (first->size == 0) {
        return 1;
    }
    if (first->data == NULL || second->data == NULL) {
        return first->data == second->data;
    }
    return memcmp(first->data, second->data,
                  first->size * sizeof(*first->data)) == 0;
}

int remove_duplicate_lists(ListOfLists *collection)
{
    int *keep;
    size_t i;
    size_t j;
    size_t write;

    if (collection == NULL) {
        return -1;
    }
    if (collection->count == 0) {
        return 0;
    }
    if (collection->lists == NULL) {
        return -1;
    }

    keep = malloc(collection->count * sizeof(*keep));
    if (keep == NULL) {
        return -1;
    }
    for (i = 0; i < collection->count; i++) {
        keep[i] = 1;
    }

    for (i = 0; i < collection->count; i++) {
        if (keep[i] == 0) {
            continue;
        }
        for (j = i + 1; j < collection->count; j++) {
            if (keep[j] == 1 &&
                lists_equal(&collection->lists[i], &collection->lists[j])) {
                keep[j] = 0;
            }
        }
    }

    write = 0;
    for (i = 0; i < collection->count; i++) {
        if (keep[i] == 1) {
            if (write != i) {
                collection->lists[write] = collection->lists[i];
                collection->lists[i].data = NULL;
                collection->lists[i].size = 0;
            }
            write++;
        } else {
            free_list(&collection->lists[i]);
        }
    }
    collection->count = write;

    free(keep);
    return 0;
}

static void print_list_of_lists(const ListOfLists *collection)
{
    size_t i;
    size_t j;

    if (collection == NULL) {
        return;
    }
    for (i = 0; i < collection->count; i++) {
        printf("[");
        for (j = 0; j < collection->lists[i].size; j++) {
            if (j > 0) {
                printf(", ");
            }
            printf("%d", collection->lists[i].data[j]);
        }
        printf("]\n");
    }
}

int main(void)
{
    int values0[] = {1, 2, 3};
    int values1[] = {4, 5};
    int values2[] = {1, 2, 3};
    int values3[] = {6, 7, 8, 9};
    int values4[] = {4, 5};
    int values5[] = {1, 2, 3};
    int values6[] = {10};

    const int *samples[] = {values0, values1, values2, values3,
                            values4, values5, values6};
    size_t sizes[] = {3, 2, 3, 4, 2, 3, 1};
    size_t total = sizeof(samples) / sizeof(samples[0]);
    size_t i;

    ListOfLists collection;

    collection.lists = calloc(total, sizeof(*collection.lists));
    if (collection.lists == NULL) {
        fprintf(stderr, "Error: memory allocation failed.\n");
        return EXIT_FAILURE;
    }
    collection.count = total;

    for (i = 0; i < total; i++) {
        if (init_list(&collection.lists[i], samples[i], sizes[i]) != 0) {
            fprintf(stderr, "Error: memory allocation failed.\n");
            free_list_of_lists(&collection);
            return EXIT_FAILURE;
        }
    }

    printf("Before removing duplicates:\n");
    print_list_of_lists(&collection);

    if (remove_duplicate_lists(&collection) != 0) {
        fprintf(stderr, "Error: could not remove duplicates.\n");
        free_list_of_lists(&collection);
        return EXIT_FAILURE;
    }

    printf("After removing duplicates:\n");
    print_list_of_lists(&collection);

    free_list_of_lists(&collection);
    return EXIT_SUCCESS;
}