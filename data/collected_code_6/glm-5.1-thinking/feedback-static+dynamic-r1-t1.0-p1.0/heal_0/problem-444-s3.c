#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    result.count = 0;
    result.tuples = NULL;

    if (list == NULL || list->count <= 0 || k < 0) {
        return result;
    }

    result.tuples = (Tuple *)malloc(list->count * sizeof(Tuple));
    if (result.tuples == NULL) {
        return result;
    }
    result.count = list->count;

    for (int i = 0; i < list->count; i++) {
        int new_size = list->tuples[i].size - 2 * k;
        if (new_size <= 0) {
            result.tuples[i].data = NULL;
            result.tuples[i].size = 0;
        } else {
            result.tuples[i].data = (int *)malloc(new_size * sizeof(int));
            if (result.tuples[i].data == NULL) {
                for (int j = 0; j < i; j++) {
                    free(result.tuples[j].data);
                }
                free(result.tuples);
                result.tuples = NULL;
                result.count = 0;
                return result;
            }
            memcpy(result.tuples[i].data, list->tuples[i].data + k, new_size * sizeof(int));
            result.tuples[i].size = new_size;
        }
    }

    return result;
}

void free_tuple_list(TupleList *list) {
    if (list == NULL || list->tuples == NULL) {
        return;
    }
    for (int i = 0; i < list->count; i++) {
        free(list->tuples[i].data);
    }
    free(list->tuples);
    list->tuples = NULL;
    list->count = 0;
}

int main(void) {
    TupleList list;
    list.count = 3;
    list.tuples = (Tuple *)malloc(list.count * sizeof(Tuple));
    if (list.tuples == NULL) {
        return EXIT_FAILURE;
    }

    int data1[] = {1, 2, 3, 4, 5};
    int data2[] = {10, 20, 30, 40, 50, 60, 70};
    int data3[] = {100, 200, 300, 400};

    list.tuples[0].data = data1;
    list.tuples[0].size = 5;
    list.tuples[1].data = data2;
    list.tuples[1].size = 7;
    list.tuples[2].data = data3;
    list.tuples[2].size = 4;

    int k = 1;

    TupleList trimmed = trim_tuples(&list, k);

    if (trimmed.tuples != NULL) {
        for (int i = 0; i < trimmed.count; i++) {
            for (int j = 0; j < trimmed.tuples[i].size; j++) {
                printf("%d ", trimmed.tuples[i].data[j]);
            }
            printf("\n");
        }
        free_tuple_list(&trimmed);
    }

    free(list.tuples);

    return EXIT_SUCCESS;
}