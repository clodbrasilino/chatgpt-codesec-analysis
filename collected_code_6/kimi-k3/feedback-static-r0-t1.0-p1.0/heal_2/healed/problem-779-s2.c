#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *data;
    size_t size;
} List;

typedef struct {
    List *lists;
    size_t count;
} ListCollection;

int compare_lists(const List *a, const List *b) {
    if (a->size != b->size) {
        return 0;
    }
    if (a->size == 0) {
        return 1;
    }
    return memcmp(a->data, b->data, a->size * sizeof(int)) == 0;
}

size_t count_unique_lists(const ListCollection *collection) {
    if (collection == NULL || collection->lists == NULL || collection->count == 0) {
        return 0;
    }

    size_t unique_count = 0;
    int *processed = calloc(collection->count, sizeof(int));
    if (processed == NULL) {
        return 0;
    }

    for (size_t i = 0; i < collection->count; i++) {
        if (processed[i]) {
            continue;
        }
        unique_count++;
        processed[i] = 1;

        for (size_t j = i + 1; j < collection->count; j++) {
            if (!processed[j] && compare_lists(&collection->lists[i], &collection->lists[j])) {
                processed[j] = 1;
            }
        }
    }

    free(processed);
    return unique_count;
}

void free_collection(ListCollection *collection) {
    if (collection == NULL) {
        return;
    }
    if (collection->lists != NULL) {
        for (size_t i = 0; i < collection->count; i++) {
            free(collection->lists[i].data);
            collection->lists[i].data = NULL;
        }
        free(collection->lists);
        collection->lists = NULL;
    }
    collection->count = 0;
}

int main(void) {
    int data1[] = {1, 2, 3};
    int data2[] = {4, 5};
    int data3[] = {1, 2, 3};
    int data4[] = {6, 7, 8, 9};
    int data5[] = {4, 5};
    int data6[] = {1, 2, 3, 4};

    ListCollection collection = {0};
    collection.count = 6;
    collection.lists = malloc(collection.count * sizeof(List));
    if (collection.lists == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < collection.count; i++) {
        collection.lists[i].data = NULL;
        collection.lists[i].size = 0;
    }

    collection.lists[0].data = malloc(sizeof(data1));
    collection.lists[1].data = malloc(sizeof(data2));
    collection.lists[2].data = malloc(sizeof(data3));
    collection.lists[3].data = malloc(sizeof(data4));
    collection.lists[4].data = malloc(sizeof(data5));
    collection.lists[5].data = malloc(sizeof(data6));

    if (collection.lists[0].data == NULL || collection.lists[1].data == NULL ||
        collection.lists[2].data == NULL || collection.lists[3].data == NULL ||
        collection.lists[4].data == NULL || collection.lists[5].data == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free_collection(&collection);
        return EXIT_FAILURE;
    }

    size_t copy_size = sizeof(data1);
    if (copy_size <= sizeof(data1)) {
        memcpy(collection.lists[0].data, data1, copy_size);
        collection.lists[0].size = copy_size / sizeof(data1[0]);
    }

    copy_size = sizeof(data2);
    if (copy_size <= sizeof(data2)) {
        memcpy(collection.lists[1].data, data2, copy_size);
        collection.lists[1].size = copy_size / sizeof(data2[0]);
    }

    copy_size = sizeof(data3);
    if (copy_size <= sizeof(data3)) {
        memcpy(collection.lists[2].data, data3, copy_size);
        collection.lists[2].size = copy_size / sizeof(data3[0]);
    }

    copy_size = sizeof(data4);
    if (copy_size <= sizeof(data4)) {
        memcpy(collection.lists[3].data, data4, copy_size);
        collection.lists[3].size = copy_size / sizeof(data4[0]);
    }

    copy_size = sizeof(data5);
    if (copy_size <= sizeof(data5)) {
        memcpy(collection.lists[4].data, data5, copy_size);
        collection.lists[4].size = copy_size / sizeof(data5[0]);
    }

    copy_size = sizeof(data6);
    if (copy_size <= sizeof(data6)) {
        memcpy(collection.lists[5].data, data6, copy_size);
        collection.lists[5].size = copy_size / sizeof(data6[0]);
    }

    size_t unique = count_unique_lists(&collection);
    printf("Number of unique lists: %zu\n", unique);

    free_collection(&collection);
    return EXIT_SUCCESS;
}