#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    int length;
} Tuple;

typedef struct {
    Tuple *data;
    int count;
    int capacity;
} TupleList;

TupleList* create_tuple_list(int capacity) {
    TupleList *list = (TupleList*)malloc(sizeof(TupleList));
    if (list == NULL) {
        exit(EXIT_FAILURE);
    }
    list->data = (Tuple*)malloc(capacity * sizeof(Tuple));
    if (list->data == NULL) {
        free(list);
        exit(EXIT_FAILURE);
    }
    list->count = 0;
    list->capacity = capacity;
    return list;
}

void add_tuple(TupleList *list, int *elements, int length) {
    if (list->count >= list->capacity) {
        int new_capacity = list->capacity * 2;
        Tuple *new_data = (Tuple*)realloc(list->data, new_capacity * sizeof(Tuple));
        if (new_data == NULL) {
            exit(EXIT_FAILURE);
        }
        list->data = new_data;
        list->capacity = new_capacity;
    }
    list->data[list->count].elements = elements;
    list->data[list->count].length = length;
    list->count++;
}

void remove_tuples_of_length_k(TupleList *list, int k) {
    if (list == NULL) {
        return;
    }
    int new_count = 0;
    for (int i = 0; i < list->count; i++) {
        if (list->data[i].length == k) {
            free(list->data[i].elements);
            list->data[i].elements = NULL;
        } else {
            list->data[new_count] = list->data[i];
            new_count++;
        }
    }
    list->count = new_count;
}

void free_tuple_list(TupleList *list) {
    if (list == NULL) {
        return;
    }
    for (int i = 0; i < list->count; i++) {
        free(list->data[i].elements);
    }
    free(list->data);
    free(list);
}

int main() {
    TupleList *list = create_tuple_list(4);

    int *e1 = (int*)malloc(2 * sizeof(int));
    e1[0] = 1; e1[1] = 2;
    add_tuple(list, e1, 2);

    int *e2 = (int*)malloc(3 * sizeof(int));
    e2[0] = 3; e2[1] = 4; e2[2] = 5;
    add_tuple(list, e2, 3);

    int *e3 = (int*)malloc(2 * sizeof(int));
    e3[0] = 6; e3[1] = 7;
    add_tuple(list, e3, 2);

    int *e4 = (int*)malloc(4 * sizeof(int));
    e4[0] = 8; e4[1] = 9; e4[2] = 10; e4[3] = 11;
    add_tuple(list, e4, 4);

    remove_tuples_of_length_k(list, 2);

    for (int i = 0; i < list->count; i++) {
        for (int j = 0; j < list->data[i].length; j++) {
            printf("%d ", list->data[i].elements[j]);
        }
        printf("\n");
    }

    free_tuple_list(list);

    return 0;
}