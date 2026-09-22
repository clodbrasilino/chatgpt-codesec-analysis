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
    if (list == NULL || list->tuples == NULL) {
        return;
    }

    size_t valid_count = 0;

    for (size_t i = 0; i < list->count; i++) {
        bool all_none = true;
        for (size_t j = 0; j < list->tuples[i].size; j++) {
            if (!list->tuples[i].is_none[j]) {
                all_none = false;
                break;
            }
        }

        if (!all_none) {
            if (valid_count != i) {
                list->tuples[valid_count] = list->tuples[i];
            }
            valid_count++;
        } else {
            free(list->tuples[i].values);
            free(list->tuples[i].is_none);
            list->tuples[i].values = NULL;
            list->tuples[i].is_none = NULL;
        }
    }

    list->count = valid_count;
}

int main() {
    size_t num_tuples = 3;
    size_t tuple_size = 2;

    Tuple* tuples = (Tuple*)malloc(num_tuples * sizeof(Tuple));
    if (tuples == NULL) {
        return 1;
    }

    for (size_t i = 0; i < num_tuples; i++) {
        tuples[i].values = (int*)malloc(tuple_size * sizeof(int));
        tuples[i].is_none = (bool*)malloc(tuple_size * sizeof(bool));
        if (tuples[i].values == NULL || tuples[i].is_none == NULL) {
            for (size_t j = 0; j <= i; j++) {
                free(tuples[j].values);
                free(tuples[j].is_none);
            }
            free(tuples);
            return 1;
        }
        tuples[i].size = tuple_size;
    }

    tuples[0].values[0] = 1; tuples[0].is_none[0] = false;
    tuples[0].values[1] = 2; tuples[0].is_none[1] = false;

    tuples[1].values[0] = 0; tuples[1].is_none[0] = true;
    tuples[1].values[1] = 0; tuples[1].is_none[1] = true;

    tuples[2].values[0] = 3; tuples[2].is_none[0] = false;
    tuples[2].values[1] = 0; tuples[2].is_none[1] = true;

    TupleList list = {tuples, num_tuples};

    remove_all_none_tuples(&list);

    for (size_t i = 0; i < list.count; i++) {
        free(list.tuples[i].values);
        free(list.tuples[i].is_none);
    }
    free(list.tuples);

    return 0;
}