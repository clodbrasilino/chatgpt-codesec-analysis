#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t len;
} Tuple;

typedef struct {
    Tuple *items;
    size_t size;
    size_t capacity;
} TupleList;

int init_list(TupleList *list, size_t capacity) {
    list->items = (Tuple *)malloc(capacity * sizeof(Tuple));
    if (!list->items) {
        return 0;
    }
    list->size = 0;
    list->capacity = capacity;
    return 1;
}

void free_tuple(Tuple *t) {
    if (t->data) {
        free(t->data);
        t->data = NULL;
        t->len = 0;
    }
}

void free_list(TupleList *list) {
    if (list->items) {
        for (size_t i = 0; i < list->size; i++) {
            free_tuple(&list->items[i]);
        }
        free(list->items);
        list->items = NULL;
        list->size = 0;
        list->capacity = 0;
    }
}

int add_tuple(TupleList *list, const int *data, size_t len) {
    if (list->size >= list->capacity) {
        size_t new_capacity = list->capacity == 0 ? 4 : list->capacity * 2;
        Tuple *new_items = (Tuple *)realloc(list->items, new_capacity * sizeof(Tuple));
        if (!new_items) {
            return 0;
        }
        list->items = new_items;
        list->capacity = new_capacity;
    }
    
    int *new_data = (int *)malloc(len * sizeof(int));
    if (!new_data) {
        return 0;
    }
    
    for (size_t i = 0; i < len; i++) {
        new_data[i] = data[i];
    }
    
    list->items[list->size].data = new_data;
    list->items[list->size].len = len;
    list->size++;
    return 1;
}

void remove_tuples_of_length_k(TupleList *list, size_t k) {
    size_t write_idx = 0;
    for (size_t read_idx = 0; read_idx < list->size; read_idx++) {
        if (list->items[read_idx].len == k) {
            free_tuple(&list->items[read_idx]);
        } else {
            if (write_idx != read_idx) {
                list->items[write_idx] = list->items[read_idx];
                list->items[read_idx].data = NULL;
                list->items[read_idx].len = 0;
            }
            write_idx++;
        }
    }
    list->size = write_idx;
}

int main(void) {
    TupleList list;
    if (!init_list(&list, 4)) {
        return EXIT_FAILURE;
    }

    int d1[] = {1, 2, 3};
    int d2[] = {4, 5};
    int d3[] = {6, 7, 8};
    int d4[] = {9};

    if (!add_tuple(&list, d1, 3) || !add_tuple(&list, d2, 2) ||
        !add_tuple(&list, d3, 3) || !add_tuple(&list, d4, 1)) {
        free_list(&list);
        return EXIT_FAILURE;
    }

    remove_tuples_of_length_k(&list, 3);

    for (size_t i = 0; i < list.size; i++) {
        for (size_t j = 0; j < list.items[i].len; j++) {
            printf("%d ", list.items[i].data[j]);
        }
        printf("\n");
    }

    free_list(&list);
    return EXIT_SUCCESS;
}