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
    TupleList list = {0};
    if (capacity > 0) {
        list.items = (Tuple *)malloc(capacity * sizeof(Tuple));
        if (list.items == NULL) {
            list.capacity = 0;
            return list;
        }
    }
    list.count = 0;
    list.capacity = capacity;
    return list;
}

void free_tuple_list(TupleList *list) {
    if (list != NULL && list->items != NULL) {
        for (size_t i = 0; i < list->count; i++) {
            if (list->items[i].elements != NULL) {
                free(list->items[i].elements);
                list->items[i].elements = NULL;
            }
        }
        free(list->items);
        list->items = NULL;
        list->count = 0;
        list->capacity = 0;
    }
}

int add_tuple(TupleList *list, const int *data, size_t data_size) {
    if (list->count >= list->capacity) {
        size_t new_capacity = list->capacity == 0 ? 4 : list->capacity * 2;
        Tuple *new_items = (Tuple *)realloc(list->items, new_capacity * sizeof(Tuple));
        if (new_items == NULL) {
            return -1;
        }
        list->items = new_items;
        list->capacity = new_capacity;
    }
    
    if (data_size > 0) {
        list->items[list->count].elements = (int *)malloc(data_size * sizeof(int));
        if (list->items[list->count].elements == NULL) {
            return -1;
        }
        if (data != NULL) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(list->items[list->count].elements, data, data_size * sizeof(int));
        } else {
            memset(list->items[list->count].elements, 0, data_size * sizeof(int));
        }
    } else {
        list->items[list->count].elements = NULL;
    }
    
    list->items[list->count].size = data_size;
    list->count++;
    
    return 0;
}

int insert_empty_tuple(TupleList *list) {
    if (list->count >= list->capacity) {
        size_t new_capacity = list->capacity == 0 ? 4 : list->capacity * 2;
        Tuple *new_items = (Tuple *)realloc(list->items, new_capacity * sizeof(Tuple));
        if (new_items == NULL) {
            return -1;
        }
        list->items = new_items;
        list->capacity = new_capacity;
    }
    
    list->items[list->count].elements = NULL;
    list->items[list->count].size = 0;
    list->count++;
    
    return 0;
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
            if (list->items[i].elements != NULL) {
                free(list->items[i].elements);
                list->items[i].elements = NULL;
            }
        }
    }

    size_t removed = list->count - valid_count;
    list->count = valid_count;

    return (int)removed;
}

int main() {
    TupleList list = create_tuple_list(2);
    if (list.items == NULL && list.capacity > 0) {
        return EXIT_FAILURE;
    }

    const int a[] = {1, 2};
    const int b[] = {0};
    const int d[] = {5, 6, 7};

    if (add_tuple(&list, a, 2) != 0) {
        free_tuple_list(&list);
        return EXIT_FAILURE;
    }
    
    if (insert_empty_tuple(&list) != 0) {
        free_tuple_list(&list);
        return EXIT_FAILURE;
    }

    if (add_tuple(&list, b, 1) != 0) {
        free_tuple_list(&list);
        return EXIT_FAILURE;
    }

    if (insert_empty_tuple(&list) != 0) {
        free_tuple_list(&list);
        return EXIT_FAILURE;
    }

    if (add_tuple(&list, d, 3) != 0) {
        free_tuple_list(&list);
        return EXIT_FAILURE;
    }

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