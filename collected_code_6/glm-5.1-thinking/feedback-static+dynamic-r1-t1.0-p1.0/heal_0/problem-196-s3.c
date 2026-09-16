#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int length;
} Tuple;

typedef struct {
    Tuple **tuples;
    int count;
    int capacity;
} TupleList;

void remove_tuples_of_length_k(TupleList *list, int k) {
    if (list == NULL || list->tuples == NULL) {
        return;
    }

    int write_idx = 0;
    for (int read_idx = 0; read_idx < list->count; read_idx++) {
        Tuple *current = list->tuples[read_idx];
        if (current != NULL && current->length == k) {
            if (current->data != NULL) {
                free(current->data);
            }
            free(current);
        } else {
            list->tuples[write_idx] = current;
            write_idx++;
        }
    }
    list->count = write_idx;
}

Tuple* create_tuple(int length) {
    Tuple *t = (Tuple*)malloc(sizeof(Tuple));
    if (t == NULL) {
        return NULL;
    }
    t->length = length;
    if (length > 0) {
        t->data = (int*)malloc(length * sizeof(int));
        if (t->data == NULL) {
            free(t);
            return NULL;
        }
        for (int i = 0; i < length; i++) {
            t->data[i] = i;
        }
    } else {
        t->data = NULL;
    }
    return t;
}

void free_list(TupleList *list) {
    if (list == NULL) {
        return;
    }
    if (list->tuples != NULL) {
        for (int i = 0; i < list->count; i++) {
            if (list->tuples[i] != NULL) {
                if (list->tuples[i]->data != NULL) {
                    free(list->tuples[i]->data);
                }
                free(list->tuples[i]);
            }
        }
        free(list->tuples);
    }
    free(list);
}

int main() {
    TupleList *list = (TupleList*)malloc(sizeof(TupleList));
    if (list == NULL) {
        return EXIT_FAILURE;
    }
    list->capacity = 5;
    list->count = 0;
    list->tuples = (Tuple**)malloc(list->capacity * sizeof(Tuple*));
    if (list->tuples == NULL) {
        free(list);
        return EXIT_FAILURE;
    }

    list->tuples[list->count++] = create_tuple(2);
    list->tuples[list->count++] = create_tuple(3);
    list->tuples[list->count++] = create_tuple(2);
    list->tuples[list->count++] = create_tuple(4);
    list->tuples[list->count++] = create_tuple(2);

    remove_tuples_of_length_k(list, 2);

    for (int i = 0; i < list->count; i++) {
        printf("Tuple %d length: %d\n", i, list->tuples[i]->length);
    }

    free_list(list);
    
    return EXIT_SUCCESS;
}