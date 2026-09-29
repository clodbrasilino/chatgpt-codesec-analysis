#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *items;
    size_t length;
} List;

typedef struct {
    List *lists;
    size_t count;
} ListOfLists;

const List *find_min_length_list(const ListOfLists *collection)
{
    const List *min_list;
    size_t i;

    if (collection == NULL || collection->lists == NULL || collection->count == 0U) {
        return NULL;
    }

    min_list = &collection->lists[0];
    for (i = 1U; i < collection->count; i++) {
        if (collection->lists[i].length < min_list->length) {
            min_list = &collection->lists[i];
        }
    }
    return min_list;
}

static int init_list(List *list, const int *values, size_t length)
{
    size_t i;

    if (list == NULL) {
        return -1;
    }

    list->items = NULL;
    list->length = 0U;

    if (length == 0U) {
        return 0;
    }

    if (values == NULL) {
        return -1;
    }

    list->items = malloc(length * sizeof(int));
    if (list->items == NULL) {
        return -1;
    }

    for (i = 0U; i < length; i++) {
        list->items[i] = values[i];
    }
    list->length = length;
    return 0;
}

static void free_collection(ListOfLists *collection)
{
    size_t i;

    if (collection == NULL || collection->lists == NULL) {
        return;
    }

    for (i = 0U; i < collection->count; i++) {
        free(collection->lists[i].items);
        collection->lists[i].items = NULL;
        collection->lists[i].length = 0U;
    }
    free(collection->lists);
    collection->lists = NULL;
    collection->count = 0U;
}

int main(void)
{
    ListOfLists collection;
    const List *result;
    size_t i;
    const int data1[] = {1, 2, 3, 4};
    const int data2[] = {5, 6};
    const int data3[] = {7, 8, 9};

    collection.count = 3U;
    collection.lists = malloc(collection.count * sizeof(List));
    if (collection.lists == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (init_list(&collection.lists[0], data1, sizeof(data1) / sizeof(data1[0])) != 0 ||
        init_list(&collection.lists[1], data2, sizeof(data2) / sizeof(data2[0])) != 0 ||
        init_list(&collection.lists[2], data3, sizeof(data3) / sizeof(data3[0])) != 0) {
        fprintf(stderr, "List initialization failed\n");
        free_collection(&collection);
        return EXIT_FAILURE;
    }

    result = find_min_length_list(&collection);
    if (result == NULL) {
        fprintf(stderr, "No minimum list found\n");
        free_collection(&collection);
        return EXIT_FAILURE;
    }

    printf("Minimum length list (length %zu): ", result->length);
    for (i = 0U; i < result->length; i++) {
        printf("%d ", result->items[i]);
    }
    printf("\n");

    free_collection(&collection);
    return EXIT_SUCCESS;
}