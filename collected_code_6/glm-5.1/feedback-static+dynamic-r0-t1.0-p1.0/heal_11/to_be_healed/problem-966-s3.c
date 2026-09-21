#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

typedef struct {
    Tuple *items;
    size_t count;
    size_t capacity;
} TupleList;

TupleList create_tuple_list() {
    TupleList list = {NULL, 0, 0};
    return list;
}

void free_tuple_list(TupleList *list) {
    if (list != NULL) {
        if (list->items != NULL) {
            for (size_t i = 0; i < list->count; i++) {
                free(list->items[i].elements);
            }
            free(list->items);
            list->items = NULL;
        }
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
                list->items[i].size = 0;
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
    if (list == NULL || (size > 0 && data == NULL)) {
        return -1;
    }
    if (list->count >= list->capacity) {
        size_t new_cap = list->capacity == 0 ? 4 : list->capacity * 2;
        Tuple *new_items = (Tuple *)realloc(list->items, new_cap * sizeof(Tuple));
        if (new_items == NULL) {
            return -1;
        }
        for (size_t i = list->capacity; i < new_cap; i++) {
            new_items[i].elements = NULL;
            new_items[i].size = 0;
        }
        list->items = new_items;
        list->capacity = new_cap;
    }
    if (size > 0) {
        if (size > SIZE_MAX / sizeof(int)) {
            return -1;
        }
        int *new_elements = (int *)malloc(size * sizeof(int));
        if (new_elements == NULL) {
            return -1;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(new_elements, data, size * sizeof(int));
        list->items[list->count].elements = new_elements;
    } else {
        list->items[list->count].elements = NULL;
    }
    list->items[list->count].size = size;
    list->count++;
    return 0;
}

int main() {
    TupleList list = create_tuple_list();
    if (list.capacity == 0 && list.items == NULL) {
        if (add_tuple(&list, NULL, 0) != 0 && list.items == NULL) {
            return EXIT_FAILURE;
        }
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