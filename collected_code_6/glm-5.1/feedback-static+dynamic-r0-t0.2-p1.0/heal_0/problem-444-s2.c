#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
} Tuple;

typedef struct {
    Tuple *tuples;
    int count;
} TupleList;

TupleList trim_tuples(const TupleList *list, int k) {
    TupleList result;
    result.count = list->count;
    result.tuples = (Tuple *)malloc(result.count * sizeof(Tuple));

    if (result.tuples == NULL) {
        result.count = 0;
        return result;
    }

    for (int i = 0; i < list->count; i++) {
        int original_size = list->tuples[i].size;
        int new_size = original_size - 2 * k;

        if (new_size <= 0) {
            result.tuples[i].data = NULL;
            result.tuples[i].size = 0;
            continue;
        }

        result.tuples[i].size = new_size;
        result.tuples[i].data = (int *)malloc(new_size * sizeof(int));

        if (result.tuples[i].data == NULL) {
            result.tuples[i].size = 0;
            for (int j = 0; j < i; j++) {
                free(result.tuples[j].data);
            }
            free(result.tuples);
            result.tuples = NULL;
            result.count = 0;
            return result;
        }

        for (int j = 0; j < new_size; j++) {
            result.tuples[i].data[j] = list->tuples[i].data[k + j];
        }
    }

    return result;
}

void free_tuple_list(TupleList *list) {
    if (list->tuples != NULL) {
        for (int i = 0; i < list->count; i++) {
            free(list->tuples[i].data);
        }
        free(list->tuples);
        list->tuples = NULL;
    }
    list->count = 0;
}

int main() {
    Tuple original_tuples[3];
    int a[] = {1, 2, 3, 4, 5};
    int b[] = {10, 20, 30, 40, 50, 60};
    int c[] = {7, 8, 9};

    original_tuples[0].data = a;
    original_tuples[0].size = 5;
    original_tuples[1].data = b;
    original_tuples[1].size = 6;
    original_tuples[2].data = c;
    original_tuples[2].size = 3;

    TupleList list;
    list.tuples = original_tuples;
    list.count = 3;

    int k = 1;
    TupleList trimmed = trim_tuples(&list, k);

    for (int i = 0; i < trimmed.count; i++) {
        for (int j = 0; j < trimmed.tuples[i].size; j++) {
            printf("%d ", trimmed.tuples[i].data[j]);
        }
        printf("\n");
    }

    free_tuple_list(&trimmed);

    return 0;
}