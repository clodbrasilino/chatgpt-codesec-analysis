#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int len;
} Tuple;

typedef struct {
    Tuple *items;
    int count;
    int capacity;
} TupleList;

TupleList* create_tuple_list(int capacity) {
    TupleList *list = (TupleList*)malloc(sizeof(TupleList));
    if (list == NULL) {
        exit(EXIT_FAILURE);
    }
    list->items = (Tuple*)malloc(capacity * sizeof(Tuple));
    if (list->items == NULL) {
        free(list);
        exit(EXIT_FAILURE);
    }
    list->count = 0;
    list->capacity = capacity;
    return list;
}

void add_tuple(TupleList *list, int *data, int len) {
    if (list->count >= list->capacity) {
        int new_capacity = list->capacity * 2;
        Tuple *new_items = (Tuple*)realloc(list->items, new_capacity * sizeof(Tuple));
        if (new_items == NULL) {
            exit(EXIT_FAILURE);
        }
        list->items = new_items;
        list->capacity = new_capacity;
    }
    list->items[list->count].data = data;
    list->items[list->count].len = len;
    list->count++;
}

void remove_tuples_of_length_k(TupleList *list, int k) {
    if (list == NULL) {
        return;
    }
    int new_count = 0;
    for (int i = 0; i < list->count; i++) {
        if (list->items[i].len != k) {
            if (new_count != i) {
                list->items[new_count] = list->items[i];
            }
            new_count++;
        } else {
            free(list->items[i].data);
        }
    }
    list->count = new_count;
}

void free_tuple_list(TupleList *list) {
    if (list == NULL) {
        return;
    }
    for (int i = 0; i < list->count; i++) {
        free(list->items[i].data);
    }
    free(list->items);
    free(list);
}

int main() {
    TupleList *list = create_tuple_list(4);

    int *d1 = (int*)malloc(2 * sizeof(int));
    d1[0] = 1; d1[1] = 2;
    add_tuple(list, d1, 2);

    int *d2 = (int*)malloc(3 * sizeof(int));
    d2[0] = 3; d2[1] = 4; d2[2] = 5;
    add_tuple(list, d2, 3);

    int *d3 = (int*)malloc(2 * sizeof(int));
    d3[0] = 6; d3[1] = 7;
    add_tuple(list, d3, 2);

    int *d4 = (int*)malloc(4 * sizeof(int));
    d4[0] = 8; d4[1] = 9; d4[2] = 10; d4[3] = 11;
    add_tuple(list, d4, 4);

    remove_tuples_of_length_k(list, 2);

    for (int i = 0; i < list->count; i++) {
        printf("Tuple %d (len %d): ", i, list->items[i].len);
        for (int j = 0; j < list->items[i].len; j++) {
            printf("%d ", list->items[i].data[j]);
        }
        printf("\n");
    }

    free_tuple_list(list);

    return 0;
}