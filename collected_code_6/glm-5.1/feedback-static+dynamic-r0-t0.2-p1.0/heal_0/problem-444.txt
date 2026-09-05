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
    if (list != NULL) {
        for (int i = 0; i < list->count; i++) {
            free(list->tuples[i].data);
        }
        free(list->tuples);
        list->count = 0;
        list->tuples = NULL;
    }
}

int main() {
    int data1[] = {1, 2, 3, 4, 5};
    int data2[] = {10, 20, 30, 40, 50, 60};
    int data3[] = {100, 200, 300};

    Tuple original_tuples[] = {
        {data1, 5},
        {data2, 6},
        {data3, 3}
    };

    TupleList original_list = {original_tuples, 3};
    int k = 1;

    TupleList trimmed_list = trim_tuples(&original_list, k);

    if (trimmed_list.tuples == NULL) {
        return 1;
    }

    for (int i = 0; i < trimmed_list.count; i++) {
        for (int j = 0; j < trimmed_list.tuples[i].size; j++) {
            printf("%d ", trimmed_list.tuples[i].data[j]);
        }
        printf("\n");
    }

    free_tuple_list(&trimmed_list);

    return 0;
}