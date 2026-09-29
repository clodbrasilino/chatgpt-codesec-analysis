#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct {
    int *data;
    size_t size;
} List;

typedef struct {
    List *lists;
    size_t count;
    size_t capacity;
} ListCollection;

static bool compare_lists(const List *a, const List *b) {
    if (a->size != b->size) {
        return false;
    }
    if (a->size == 0) {
        return true;
    }
    if (a->data == NULL || b->data == NULL) {
        return false;
    }
    return memcmp(a->data, b->data, a->size * sizeof(int)) == 0;
}

static bool list_exists(const ListCollection *collection, const List *target) {
    for (size_t i = 0; i < collection->count; i++) {
        if (compare_lists(&collection->lists[i], target)) {
            return true;
        }
    }
    return false;
}

static void free_list(List *list) {
    if (list != NULL) {
        free(list->data);
        list->data = NULL;
        list->size = 0;
    }
}

static void free_collection(ListCollection *collection) {
    if (collection != NULL) {
        if (collection->lists != NULL) {
            for (size_t i = 0; i < collection->count; i++) {
                free_list(&collection->lists[i]);
            }
            free(collection->lists);
            collection->lists = NULL;
        }
        collection->count = 0;
        collection->capacity = 0;
    }
}

static bool add_list_copy(ListCollection *collection, const int *data, size_t size) {
    if (collection->count >= collection->capacity) {
        size_t new_capacity = collection->capacity == 0 ? 4 : collection->capacity * 2;
        if (new_capacity < collection->capacity) {
            return false;
        }
        if (new_capacity > SIZE_MAX / sizeof(List)) {
            return false;
        }
        List *new_lists = realloc(collection->lists, new_capacity * sizeof(List));
        if (new_lists == NULL) {
            return false;
        }
        collection->lists = new_lists;
        collection->capacity = new_capacity;
    }

    int *new_data = NULL;
    if (size > 0) {
        if (data == NULL) {
            return false;
        }
        if (size > SIZE_MAX / sizeof(int)) {
            return false;
        }
        size_t copy_size = size * sizeof(int);
        new_data = malloc(copy_size);
        if (new_data == NULL) {
            return false;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(new_data, data, copy_size);
    }

    collection->lists[collection->count].data = new_data;
    collection->lists[collection->count].size = size;
    collection->count++;
    return true;
}

static size_t count_unique_lists(const int *flat_data, const size_t *sizes, size_t num_lists) {
    if (flat_data == NULL || sizes == NULL) {
        return 0;
    }

    ListCollection unique = {NULL, 0, 0};
    size_t offset = 0;

    for (size_t i = 0; i < num_lists; i++) {
        List temp;
        temp.data = (int *)(flat_data + offset);
        temp.size = sizes[i];

        if (!list_exists(&unique, &temp)) {
            if (!add_list_copy(&unique, flat_data + offset, sizes[i])) {
                free_collection(&unique);
                return 0;
            }
        }
        offset += sizes[i];
    }

    size_t result = unique.count;
    free_collection(&unique);
    return result;
}

int main(void) {
    const int data[] = {
        1, 2, 3,
        4, 5,
        1, 2, 3,
        6,
        4, 5,
        7, 8, 9, 10,
        1, 2, 3
    };
    const size_t sizes[] = {3, 2, 3, 1, 2, 4, 3};
    size_t num_lists = sizeof(sizes) / sizeof(sizes[0]);
    size_t unique_count = count_unique_lists(data, sizes, num_lists);
    printf("Number of unique lists: %zu\n", unique_count);
    return 0;
}