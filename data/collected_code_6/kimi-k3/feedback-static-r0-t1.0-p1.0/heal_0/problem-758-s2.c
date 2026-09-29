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
    size_t capacity;
} ListCollection;

static int compare_lists(const List *a, const List *b) {
    if (a->size != b->size) {
        return 0;
    }
    if (a->size == 0) {
        return 1;
    }
    return memcmp(a->data, b->data, a->size * sizeof(int)) == 0;
}

static int list_exists(const ListCollection *collection, const List *target) {
    size_t i;
    for (i = 0; i < collection->count; i++) {
        if (compare_lists(&collection->lists[i], target)) {
            return 1;
        }
    }
    return 0;
}

static void free_list(List *list) {
    if (list != NULL) {
        free(list->data);
        list->data = NULL;
        list->size = 0;
    }
}

static void free_collection(ListCollection *collection) {
    size_t i;
    if (collection != NULL) {
        if (collection->lists != NULL) {
            for (i = 0; i < collection->count; i++) {
                free_list(&collection->lists[i]);
            }
            free(collection->lists);
            collection->lists = NULL;
        }
        collection->count = 0;
        collection->capacity = 0;
    }
}

static int add_list_copy(ListCollection *collection, const int *data, size_t size) {
    List *new_lists;
    int *new_data;
    size_t new_capacity;

    if (collection->count >= collection->capacity) {
        new_capacity = collection->capacity == 0 ? 4 : collection->capacity * 2;
        if (new_capacity < collection->capacity) {
            return 0;
        }
        new_lists = realloc(collection->lists, new_capacity * sizeof(List));
        if (new_lists == NULL) {
            return 0;
        }
        collection->lists = new_lists;
        collection->capacity = new_capacity;
    }

    if (size > 0) {
        new_data = malloc(size * sizeof(int));
        if (new_data == NULL) {
            return 0;
        }
        memcpy(new_data, data, size * sizeof(int));
    } else {
        new_data = NULL;
    }

    collection->lists[collection->count].data = new_data;
    collection->lists[collection->count].size = size;
    collection->count++;
    return 1;
}

static size_t count_unique_lists(const int *flat_data, const size_t *sizes, size_t num_lists) {
    ListCollection unique;
    List temp;
    size_t i;
    size_t offset;
    size_t result;

    if (flat_data == NULL || sizes == NULL) {
        return 0;
    }

    unique.lists = NULL;
    unique.count = 0;
    unique.capacity = 0;
    offset = 0;

    for (i = 0; i < num_lists; i++) {
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

    result = unique.count;
    free_collection(&unique);
    return result;
}

int main(void) {
    int data[] = {
        1, 2, 3,
        4, 5,
        1, 2, 3,
        6,
        4, 5,
        7, 8, 9, 10,
        1, 2, 3
    };
    size_t sizes[] = {3, 2, 3, 1, 2, 4, 3};
    size_t num_lists = sizeof(sizes) / sizeof(sizes[0]);
    size_t unique_count;

    unique_count = count_unique_lists(data, sizes, num_lists);
    printf("Number of unique lists: %zu\n", unique_count);

    return 0;
}