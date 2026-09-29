#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    void **values;
    size_t size;
} Tuple;

typedef struct {
    Tuple *tuples;
    size_t size;
} TupleList;

bool tuple_is_all_none(const Tuple *tuple) {
    if (tuple == NULL || tuple->values == NULL) {
        return true;
    }
    for (size_t i = 0; i < tuple->size; i++) {
        if (tuple->values[i] != NULL) {
            return false;
        }
    }
    return true;
}

void tuple_destroy(Tuple *tuple) {
    if (tuple == NULL) {
        return;
    }
    free(tuple->values);
    tuple->values = NULL;
    tuple->size = 0;
}

void tuple_list_remove_all_none(TupleList *list) {
    if (list == NULL || list->tuples == NULL) {
        return;
    }

    size_t write_index = 0;
    for (size_t read_index = 0; read_index < list->size; read_index++) {
        if (!tuple_is_all_none(&list->tuples[read_index])) {
            if (write_index != read_index) {
                list->tuples[write_index] = list->tuples[read_index];
            }
            write_index++;
        } else {
            tuple_destroy(&list->tuples[read_index]);
        }
    }

    list->size = write_index;
    if (write_index == 0) {
        free(list->tuples);
        list->tuples = NULL;
    } else {
        Tuple *new_tuples = realloc(list->tuples, write_index * sizeof(Tuple));
        if (new_tuples != NULL) {
            list->tuples = new_tuples;
        }
    }
}

void tuple_list_destroy(TupleList *list) {
    if (list == NULL) {
        return;
    }
    for (size_t i = 0; i < list->size; i++) {
        tuple_destroy(&list->tuples[i]);
    }
    free(list->tuples);
    list->tuples = NULL;
    list->size = 0;
}

Tuple tuple_create(size_t size) {
    Tuple tuple;
    tuple.size = size;
    tuple.values = calloc(size, sizeof(void *));
    return tuple;
}

int main(void) {
    TupleList list;
    list.size = 4;
    list.tuples = malloc(list.size * sizeof(Tuple));

    list.tuples[0] = tuple_create(3);
    list.tuples[0].values[0] = (void *)1;
    list.tuples[0].values[1] = NULL;
    list.tuples[0].values[2] = NULL;

    list.tuples[1] = tuple_create(2);
    list.tuples[1].values[0] = NULL;
    list.tuples[1].values[1] = NULL;

    list.tuples[2] = tuple_create(4);
    list.tuples[2].values[0] = NULL;
    list.tuples[2].values[1] = (void *)2;
    list.tuples[2].values[2] = NULL;
    list.tuples[2].values[3] = NULL;

    list.tuples[3] = tuple_create(1);
    list.tuples[3].values[0] = NULL;

    tuple_list_remove_all_none(&list);

    printf("Remaining tuples: %zu\n", list.size);
    for (size_t i = 0; i < list.size; i++) {
        printf("Tuple %zu: ", i);
        for (size_t j = 0; j < list.tuples[i].size; j++) {
            if (list.tuples[i].values[j] != NULL) {
                printf("value ");
            } else {
                printf("NULL ");
            }
        }
        printf("\n");
    }

    tuple_list_destroy(&list);

    return 0;
}