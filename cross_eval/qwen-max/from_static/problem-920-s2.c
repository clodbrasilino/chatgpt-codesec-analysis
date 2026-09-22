#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* values;
    int size;
} Tuple;

typedef struct {
    Tuple* tuples;
    int count;
    int capacity;
} TupleList;

Tuple* create_tuple(int size) {
    Tuple* t = (Tuple*)malloc(sizeof(Tuple));
    if (t == NULL) return NULL;
    t->values = (int*)calloc(size, sizeof(int));
    if (t->values == NULL) {
        free(t);
        return NULL;
    }
    t->size = size;
    return t;
}

TupleList* create_tuple_list(int capacity) {
    TupleList* tl = (TupleList*)malloc(sizeof(TupleList));
    if (tl == NULL) return NULL;
    tl->tuples = (Tuple*)malloc(capacity * sizeof(Tuple));
    if (tl->tuples == NULL) {
        free(tl);
        return NULL;
    }
    tl->count = 0;
    tl->capacity = capacity;
    return tl;
}

void free_tuple(Tuple* tuple) {
    if (tuple != NULL) {
        free(tuple->values);
        free(tuple);
    }
}

void free_tuple_list(TupleList* list) {
    if (list != NULL) {
        for (int i = 0; i < list->count; i++) {
            free_tuple(&list->tuples[i]);
        }
        free(list->tuples);
        free(list);
    }
}

int all_none(Tuple* tuple) {
    for (int i = 0; i < tuple->size; i++) {
        if (tuple->values[i] != 0) return 0;
    }
    return 1;
}

TupleList* remove_all_none_tuples(TupleList* list) {
    int new_count = 0;
    TupleList* new_list = create_tuple_list(list->count);
    if (new_list == NULL) return NULL;

    for (int i = 0; i < list->count; i++) {
        if (!all_none(&list->tuples[i])) {
            new_list->tuples[new_count++] = list->tuples[i];
        } else {
            free_tuple(&list->tuples[i]);
        }
    }

    new_list->count = new_count;
    return new_list;
}

int main() {
    TupleList* list = create_tuple_list(5);
    if (list == NULL) return 1;

    for (int i = 0; i < 5; i++) {
        list->tuples[list->count] = *create_tuple(3);
        list->count++;
    }

    // Initialize tuples with some values
    list->tuples[0].values[0] = 1;
    list->tuples[1].values[0] = 0;
    list->tuples[2].values[0] = 2;
    list->tuples[3].values[0] = 0;
    list->tuples[4].values[0] = 3;

    TupleList* filtered_list = remove_all_none_tuples(list);

    if (filtered_list != NULL) {
        for (int i = 0; i < filtered_list->count; i++) {
            for (int j = 0; j < filtered_list->tuples[i].size; j++) {
                printf("%d ", filtered_list->tuples[i].values[j]);
            }
            printf("\n");
        }
        free_tuple_list(filtered_list);
    }

    free_tuple_list(list);
    return 0;
}