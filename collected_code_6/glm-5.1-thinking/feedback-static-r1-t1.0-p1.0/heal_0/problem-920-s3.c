#include <stdio.h>
#include <stdlib.h>

#define TUPLE_SIZE 3

typedef struct {
    int* elements[TUPLE_SIZE];
} Tuple;

typedef struct {
    Tuple* data;
    int size;
} TupleList;

int is_all_none(const Tuple* t) {
    if (t == NULL) {
        return 1;
    }
    for (int i = 0; i < TUPLE_SIZE; i++) {
        if (t->elements[i] != NULL) {
            return 0;
        }
    }
    return 1;
}

void remove_all_none_tuples(TupleList* list) {
    if (list == NULL || list->data == NULL) {
        return;
    }
    int write_idx = 0;
    for (int read_idx = 0; read_idx < list->size; read_idx++) {
        if (!is_all_none(&list->data[read_idx])) {
            list->data[write_idx++] = list->data[read_idx];
        }
    }
    list->size = write_idx;
    if (list->size == 0) {
        free(list->data);
        list->data = NULL;
    } else {
        Tuple* new_data = realloc(list->data, list->size * sizeof(Tuple));
        if (new_data != NULL) {
            list->data = new_data;
        }
    }
}

int main(void) {
    int a = 1, b = 2;
    TupleList list;
    list.size = 4;
    list.data = malloc(list.size * sizeof(Tuple));
    if (list.data == NULL) {
        return EXIT_FAILURE;
    }
    list.data[0].elements[0] = &a;
    list.data[0].elements[1] = NULL;
    list.data[0].elements[2] = NULL;
    list.data[1].elements[0] = NULL;
    list.data[1].elements[1] = NULL;
    list.data[1].elements[2] = NULL;
    list.data[2].elements[0] = NULL;
    list.data[2].elements[1] = &b;
    list.data[2].elements[2] = NULL;
    list.data[3].elements[0] = NULL;
    list.data[3].elements[1] = NULL;
    list.data[3].elements[2] = NULL;

    remove_all_none_tuples(&list);

    for (int i = 0; i < list.size; i++) {
        for (int j = 0; j < TUPLE_SIZE; j++) {
            if (list.data[i].elements[j] != NULL) {
                printf("%d ", *list.data[i].elements[j]);
            } else {
                printf("None ");
            }
        }
        printf("\n");
    }

    free(list.data);
    return EXIT_SUCCESS;
}