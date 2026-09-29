#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    int *data;
    size_t size;
} Tuple;

typedef struct {
    Tuple *items;
    size_t count;
    size_t capacity;
} TupleList;

int init_tuple_list(TupleList *list, size_t capacity) {
    if (list == NULL) {
        return -1;
    }
    list->items = NULL;
    list->count = 0;
    list->capacity = 0;
    if (capacity == 0) {
        return 0;
    }
    if (capacity > SIZE_MAX / sizeof(Tuple)) {
        return -1;
    }
    list->items = (Tuple *)calloc(capacity, sizeof(Tuple));
    if (list->items == NULL) {
        return -1;
    }
    list->capacity = capacity;
    return 0;
}

Tuple create_tuple(const int *data, size_t size) {
    Tuple t;
    t.data = NULL;
    t.size = 0;
    if (data == NULL || size == 0) {
        return t;
    }
    if (size > SIZE_MAX / sizeof(int)) {
        return t;
    }
    size_t bytes = size * sizeof(int);
    t.data = (int *)malloc(bytes);
    if (t.data == NULL) {
        return t;
    }
    memcpy(t.data, data, bytes);
    t.size = size;
    return t;
}

int add_tuple(TupleList *list, Tuple t) {
    if (list == NULL) {
        return -1;
    }
    if (list->count > list->capacity) {
        return -1;
    }
    if (list->count >= list->capacity) {
        size_t new_capacity;
        if (list->capacity == 0) {
            new_capacity = 4;
        } else {
            if (list->capacity > SIZE_MAX / 2) {
                return -1;
            }
            new_capacity = list->capacity * 2;
        }
        if (new_capacity > SIZE_MAX / sizeof(Tuple)) {
            return -1;
        }
        Tuple *new_items = (Tuple *)realloc(list->items, new_capacity * sizeof(Tuple));
        if (new_items == NULL) {
            return -1;
        }
        list->items = new_items;
        list->capacity = new_capacity;
    }
    list->items[list->count] = t;
    list->count++;
    return 0;
}

int add_tuple_data(TupleList *list, const int *data, size_t size) {
    Tuple t = create_tuple(data, size);
    if (data != NULL && size > 0 && t.data == NULL) {
        return -1;
    }
    if (add_tuple(list, t) != 0) {
        free(t.data);
        return -1;
    }
    return 0;
}

size_t remove_empty_tuples(TupleList *list) {
    if (list == NULL || list->items == NULL) {
        return 0;
    }
    if (list->count > list->capacity) {
        return 0;
    }
    size_t write = 0;
    size_t removed = 0;
    for (size_t read = 0; read < list->count && read < list->capacity; read++) {
        if (list->items[read].data != NULL && list->items[read].size > 0) {
            if (write != read) {
                list->items[write] = list->items[read];
                list->items[read].data = NULL;
                list->items[read].size = 0;
            }
            write++;
        } else {
            free(list->items[read].data);
            list->items[read].data = NULL;
            list->items[read].size = 0;
            removed++;
        }
    }
    for (size_t i = write; i < list->count && i < list->capacity; i++) {
        list->items[i].data = NULL;
        list->items[i].size = 0;
    }
    list->count = write;
    return removed;
}

void print_tuple_list(const TupleList *list) {
    if (list == NULL) {
        return;
    }
    size_t limit = list->count;
    if (list->items == NULL) {
        limit = 0;
    } else if (limit > list->capacity) {
        limit = list->capacity;
    }
    printf("[");
    for (size_t i = 0; i < limit; i++) {
        printf("(");
        const Tuple *t = &list->items[i];
        if (t->data != NULL) {
            for (size_t j = 0; j < t->size; j++) {
                printf("%d", t->data[j]);
                if (j + 1 < t->size) {
                    printf(", ");
                }
            }
        }
        printf(")");
        if (i + 1 < limit) {
            printf(", ");
        }
    }
    printf("]\n");
}

void free_tuple_list(TupleList *list) {
    if (list == NULL) {
        return;
    }
    size_t limit = list->count;
    if (list->items == NULL) {
        limit = 0;
    } else if (limit > list->capacity) {
        limit = list->capacity;
    }
    for (size_t i = 0; i < limit; i++) {
        free(list->items[i].data);
        list->items[i].data = NULL;
        list->items[i].size = 0;
    }
    free(list->items);
    list->items = NULL;
    list->count = 0;
    list->capacity = 0;
}

int main(void) {
    TupleList list;
    if (init_tuple_list(&list, 0) != 0) {
        fprintf(stderr, "Error: failed to initialize tuple list.\n");
        return EXIT_FAILURE;
    }

    const int d1[] = {1, 2, 3};
    const int d2[] = {4, 5};
    const int d3[] = {7, 8, 9, 10};

    if (add_tuple_data(&list, d1, 3) != 0 ||
        add_tuple_data(&list, NULL, 0) != 0 ||
        add_tuple_data(&list, d2, 2) != 0 ||
        add_tuple_data(&list, NULL, 0) != 0 ||
        add_tuple_data(&list, d3, 4) != 0) {
        fprintf(stderr, "Error: failed to add tuple.\n");
        free_tuple_list(&list);
        return EXIT_FAILURE;
    }

    printf("Original list: ");
    print_tuple_list(&list);

    size_t removed = remove_empty_tuples(&list);

    printf("Removed %zu empty tuple(s).\n", removed);
    printf("Updated list:  ");
    print_tuple_list(&list);

    free_tuple_list(&list);
    return EXIT_SUCCESS;
}