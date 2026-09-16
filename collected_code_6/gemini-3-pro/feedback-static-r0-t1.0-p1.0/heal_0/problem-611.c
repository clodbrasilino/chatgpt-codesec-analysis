#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int* data;
    size_t cols;
} Tuple;

typedef struct {
    Tuple* tuples;
    size_t rows;
} TupleList;

int find_max_nth_column(const TupleList* list, size_t n, int* max_val) {
    if (list == NULL || list->tuples == NULL || list->rows == 0 || max_val == NULL) {
        return -1;
    }

    *max_val = INT_MIN;
    int found = 0;

    for (size_t i = 0; i < list->rows; i++) {
        if (list->tuples[i].data != NULL && n < list->tuples[i].cols) {
            if (list->tuples[i].data[n] > *max_val) {
                *max_val = list->tuples[i].data[n];
            }
            found = 1;
        }
    }

    return found ? 0 : -1;
}

int main(void) {
    size_t rows = 3;
    size_t cols = 4;
    size_t n = 2;

    TupleList list;
    list.rows = rows;
    list.tuples = (Tuple*)malloc(rows * sizeof(Tuple));
    if (list.tuples == NULL) {
        return 1;
    }

    for (size_t i = 0; i < rows; i++) {
        list.tuples[i].cols = cols;
        list.tuples[i].data = (int*)malloc(cols * sizeof(int));
        if (list.tuples[i].data == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(list.tuples[j].data);
            }
            free(list.tuples);
            return 1;
        }
    }

    list.tuples[0].data[0] = 1; list.tuples[0].data[1] = 2; list.tuples[0].data[2] = 3; list.tuples[0].data[3] = 4;
    list.tuples[1].data[0] = 5; list.tuples[1].data[1] = 6; list.tuples[1].data[2] = 9; list.tuples[1].data[3] = 8;
    list.tuples[2].data[0] = 9; list.tuples[2].data[1] = 10; list.tuples[2].data[2] = 1; list.tuples[2].data[3] = 12;

    int max_val;
    if (find_max_nth_column(&list, n, &max_val) == 0) {
        printf("Maximum of column %zu is %d\n", n, max_val);
    } else {
        printf("Error or column %zu not found\n", n);
    }

    for (size_t i = 0; i < rows; i++) {
        free(list.tuples[i].data);
        list.tuples[i].data = NULL;
    }
    free(list.tuples);
    list.tuples = NULL;

    return 0;
}