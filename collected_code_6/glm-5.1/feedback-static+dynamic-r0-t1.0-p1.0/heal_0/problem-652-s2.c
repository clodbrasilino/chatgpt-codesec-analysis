#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int val1;
    int val2;
} Tuple;

typedef struct {
    Tuple* data;
    int size;
    int capacity;
} TupleList;

TupleList* flatten_tuple_matrix(Tuple** matrix, int rows, int cols) {
    TupleList* list = malloc(sizeof(TupleList));
    if (!list) {
        return NULL;
    }

    list->size = 0;
    list->capacity = cols;
    list->data = malloc(cols * sizeof(Tuple));
    if (!list->data) {
        free(list);
        return NULL;
    }

    for (int c = 0; c < cols; c++) {
        int sum1 = 0;
        int sum2 = 0;
        for (int r = 0; r < rows; r++) {
            sum1 += matrix[r][c].val1;
            sum2 += matrix[r][c].val2;
        }
        list->data[list->size].val1 = sum1;
        list->data[list->size].val2 = sum2;
        list->size++;
    }

    return list;
}

int main() {
    int rows = 3;
    int cols = 2;

    Tuple** matrix = malloc(rows * sizeof(Tuple*));
    if (!matrix) {
        return 1;
    }
    for (int i = 0; i < rows; i++) {
        matrix[i] = malloc(cols * sizeof(Tuple));
        if (!matrix[i]) {
            for (int j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            return 1;
        }
    }

    matrix[0][0].val1 = 1; matrix[0][0].val2 = 2;
    matrix[0][1].val1 = 3; matrix[0][1].val2 = 4;
    matrix[1][0].val1 = 5; matrix[1][0].val2 = 6;
    matrix[1][1].val1 = 7; matrix[1][1].val2 = 8;
    matrix[2][0].val1 = 9; matrix[2][0].val2 = 10;
    matrix[2][1].val1 = 11; matrix[2][1].val2 = 12;

    TupleList* list = flatten_tuple_matrix(matrix, rows, cols);
    if (!list) {
        for (int i = 0; i < rows; i++) {
            free(matrix[i]);
        }
        free(matrix);
        return 1;
    }

    for (int i = 0; i < list->size; i++) {
        printf("(%d, %d)\n", list->data[i].val1, list->data[i].val2);
    }

    free(list->data);
    free(list);

    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}