#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

typedef struct {
    Tuple *items;
    size_t count;
    size_t capacity;
} TupleList;

TupleList create_tuple_list(size_t capacity) {
    TupleList list;
    list.items = (Tuple *)malloc(capacity * sizeof(Tuple));
    if (list.items != NULL) {
        for (size_t i = 0; i < capacity; i++) {
            list.items[i].elements = NULL;
            list.items[i].size = 0;
        }
    }
    list.count = 0;
    list.capacity = capacity;
    return list;
}

void free_tuple_list(TupleList *list) {
    if (list != NULL && list->items != NULL) {
        for (size_t i = 0; i < list->capacity; i++) {
            free(list->items[i].elements);
        }
        free(list->items);
        list->items = NULL;
        list->count = 0;
        list->capacity = 0;
    }
}

int remove_empty_tuples(TupleList *list) {
    if (list == NULL || list->items == NULL) {
        return -1;
    }

    size_t valid_count = 0;
    for (size_t i = 0; i < list->count; i++) {
        if (list->items[i].size > 0) {
            if (valid_count != i) {
                list->items[valid_count] = list->items[i];
                list->items[i].elements = NULL;
            }
            valid_count++;
        } else {
            free(list->items[i].elements);
            list->items[i].elements = NULL;
        }
    }

    int removed = (int)(list->count - valid_count);
    list->count = valid_count;

    return removed;
}

int add_tuple(TupleList *list, const int *data, size_t size) {
    if (list == NULL || list->items == NULL || (size > 0 && data == NULL)) {
        return -1;
    }
    if (list->count >= list->capacity) {
        return -1;
    }
    if (size > 0) {
        int *new_elements = (int *)malloc(size * sizeof(int));
        if (new_elements == NULL) {
            return -1;
        }
        if (size > SIZE_MAX / sizeof(int) || size * sizeof(int) > SIZE_MAX) {
            free(new_elements);
            return -1;
        }
        size_t safe_size = size * sizeof(int);
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(new_elements, data, safe_size);
        list->items[list->count].elements = new_elements;
    } else {
        list->items[list->count].elements = NULL;
    }
    list->items[list->count].size = size;
    list->count++;
    return 0;
}

int main() {
    size_t capacity = 5;
    TupleList list = create_tuple_list(capacity);
    if (list.items == NULL) {
        return EXIT_FAILURE;
    }

    const int a[] = {1, 2};
    const int b[] = {0};
    const int d[] = {5, 6, 7};

    add_tuple(&list, a, 2);
    add_tuple(&list, NULL, 0);
    add_tuple(&list, b, 1);
    add_tuple(&list, NULL, 0);
    add_tuple(&list, d, 3);

    for (size_t i = 0; i < list.count; i++) {
        printf("Tuple %zu: size=%zu\n", i, list.items[i].size);
    }

    int removed = remove_empty_tuples(&list);
    printf("Removed: %d\n", removed);

    for (size_t i = 0; i < list.count; i++) {
        printf("Tuple %zu: size=%zu\n", i, list.items[i].size);
    }

    free_tuple_list(&list);

    return EXIT_SUCCESS;
}