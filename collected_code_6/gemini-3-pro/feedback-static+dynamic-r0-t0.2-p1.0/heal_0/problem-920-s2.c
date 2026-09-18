#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int* values;
    bool* is_none;
    size_t size;
} Tuple;

typedef struct {
    Tuple* tuples;
    size_t count;
} TupleList;

bool is_all_none(const Tuple* tuple) {
    if (!tuple || !tuple->is_none) return false;
    for (size_t i = 0; i < tuple->size; ++i) {
        if (!tuple->is_none[i]) {
            return false;
        }
    }
    return true;
}

void free_tuple(Tuple* tuple) {
    if (tuple) {
        free(tuple->values);
        free(tuple->is_none);
        tuple->values = NULL;
        tuple->is_none = NULL;
        tuple->size = 0;
    }
}

void remove_all_none_tuples(TupleList* list) {
    if (!list || !list->tuples) return;

    size_t write_index = 0;
    for (size_t read_index = 0; read_index < list->count; ++read_index) {
        if (is_all_none(&list->tuples[read_index])) {
            free_tuple(&list->tuples[read_index]);
        } else {
            if (write_index != read_index) {
                list->tuples[write_index] = list->tuples[read_index];
            }
            write_index++;
        }
    }
    list->count = write_index;
}

int main(void) {
    TupleList list;
    list.count = 3;
    list.tuples = malloc(list.count * sizeof(Tuple));
    if (!list.tuples) return 1;

    for (size_t i = 0; i < list.count; ++i) {
        list.tuples[i].size = 2;
        list.tuples[i].values = malloc(2 * sizeof(int));
        list.tuples[i].is_none = malloc(2 * sizeof(bool));
        if (!list.tuples[i].values || !list.tuples[i].is_none) {
            for (size_t j = 0; j <= i; ++j) free_tuple(&list.tuples[j]);
            free(list.tuples);
            return 1;
        }
    }

    list.tuples[0].values[0] = 1; list.tuples[0].is_none[0] = false;
    list.tuples[0].values[1] = 2; list.tuples[0].is_none[1] = false;

    list.tuples[1].values[0] = 0; list.tuples[1].is_none[0] = true;
    list.tuples[1].values[1] = 0; list.tuples[1].is_none[1] = true;

    list.tuples[2].values[0] = 3; list.tuples[2].is_none[0] = false;
    list.tuples[2].values[1] = 0; list.tuples[2].is_none[1] = true;

    remove_all_none_tuples(&list);

    for (size_t i = 0; i < list.count; ++i) {
        free_tuple(&list.tuples[i]);
    }
    free(list.tuples);

    return 0;
}