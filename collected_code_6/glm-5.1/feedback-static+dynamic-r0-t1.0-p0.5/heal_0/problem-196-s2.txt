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
        return NULL;
    }
    list->data = (Tuple*)malloc(capacity * sizeof(Tuple));
    if (list->data == NULL) {
        free(list);
        return NULL;
    }
    list->count = 0;
    list->capacity = capacity;
    return list;
}

int insert_tuple(TupleList *list, int *elements, int length) {
    if (list == NULL || list->count >= list->capacity) {
        return -1;
    }
    list->data[list->count].elements = elements;
    list->data[list->count].length = length;
    list->count++;
    return 0;
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
            if (new_count != i) {
                list->data[new_count] = list->data[i];
                list->data[i].elements = NULL;
                list->data[i].length = 0;
            }
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

int main(void) {
    int capacity = 5;
    TupleList *list = create_tuple_list(capacity);
    if (list == NULL) {
        return 1;
    }

    int e1[] = {1, 2};
    int e2[] = {3, 4, 5};
    int e3[] = {6};
    int e4[] = {7, 8};
    int e5[] = {9, 10, 11, 12};

    insert_tuple(list, e1, 2);
    insert_tuple(list, e2, 3);
    insert_tuple(list, e3, 1);
    insert_tuple(list, e4, 2);
    insert_tuple(list, e5, 4);

    remove_tuples_of_length_k(list, 2);

    for (int i = 0; i < list->count; i++) {
        printf("Tuple %d (length %d): ", i, list->data[i].length);
        for (int j = 0; j < list->data[i].length; j++) {
            printf("%d ", list->data[i].elements[j]);
        }
        printf("\n");
    }

    free_tuple_list(list);

    return 0;
}