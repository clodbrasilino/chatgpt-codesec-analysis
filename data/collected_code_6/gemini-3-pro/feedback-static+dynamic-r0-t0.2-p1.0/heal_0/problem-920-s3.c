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

void remove_all_none_tuples(TupleList* list) {
    if (!list || !list->tuples) return;

    size_t write_index = 0;

    for (size_t i = 0; i < list->count; ++i) {
        bool all_none = true;
        for (size_t j = 0; j < list->tuples[i].size; ++j) {
            if (!list->tuples[i].is_none[j]) {
                all_none = false;
                break;
            }
        }

        if (all_none) {
            free(list->tuples[i].values);
            free(list->tuples[i].is_none);
            list->tuples[i].values = NULL;
            list->tuples[i].is_none = NULL;
        } else {
            if (write_index != i) {
                list->tuples[write_index] = list->tuples[i];
            }
            write_index++;
        }
    }

    list->count = write_index;
}

int main() {
    TupleList list;
    list.count = 3;
    list.tuples = (Tuple*)malloc(list.count * sizeof(Tuple));
    if (!list.tuples) return 1;

    for (size_t i = 0; i < list.count; ++i) {
        list.tuples[i].size = 2;
        list.tuples[i].values = (int*)malloc(2 * sizeof(int));
        list.tuples[i].is_none = (bool*)malloc(2 * sizeof(bool));
        if (!list.tuples[i].values || !list.tuples[i].is_none) {
            for (size_t j = 0; j <= i; ++j) {
                free(list.tuples[j].values);
                free(list.tuples[j].is_none);
            }
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
        free(list.tuples[i].values);
        free(list.tuples[i].is_none);
    }
    free(list.tuples);

    return 0;
}