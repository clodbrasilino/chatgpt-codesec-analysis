#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int **data;
    size_t rows;
    size_t cols;
} NestedTuple;

NestedTuple* create_nested_tuple(size_t rows, size_t cols) {
    NestedTuple* tuple = malloc(sizeof(NestedTuple));
    if (!tuple) {
        return NULL;
    }

    tuple->rows = rows;
    tuple->cols = cols;
    tuple->data = malloc(rows * sizeof(int*));
    if (!tuple->data) {
        free(tuple);
        return NULL;
    }

    for (size_t i = 0; i < rows; i++) {
        tuple->data[i] = malloc(cols * sizeof(int));
        if (!tuple->data[i]) {
            for (size_t j = 0; j < i; j++) {
                free(tuple->data[j]);
            }
            free(tuple->data);
            free(tuple);
            return NULL;
        }
    }

    return tuple;
}

void free_nested_tuple(NestedTuple* tuple) {
    if (!tuple) {
        return;
    }
    for (size_t i = 0; i < tuple->rows; i++) {
        free(tuple->data[i]);
    }
    free(tuple->data);
    free(tuple);
}

NestedTuple* subtract_nested_tuples(const NestedTuple* t1, const NestedTuple* t2) {
    if (!t1 || !t2 || t1->rows != t2->rows || t1->cols != t2->cols) {
        return NULL;
    }

    NestedTuple* result = create_nested_tuple(t1->rows, t1->cols);
    if (!result) {
        return NULL;
    }

    for (size_t i = 0; i < t1->rows; i++) {
        for (size_t j = 0; j < t1->cols; j++) {
            result->data[i][j] = t1->data[i][j] - t2->data[i][j];
        }
    }

    return result;
}

int main(void) {
    size_t rows = 2;
    size_t cols = 2;

    NestedTuple* t1 = create_nested_tuple(rows, cols);
    NestedTuple* t2 = create_nested_tuple(rows, cols);

    if (!t1 || !t2) {
        free_nested_tuple(t1);
        free_nested_tuple(t2);
        return 1;
    }

    t1->data[0][0] = 5;
    t1->data[0][1] = 6;
    t1->data[1][0] = 7;
    t1->data[1][1] = 8;

    t2->data[0][0] = 1;
    t2->data[0][1] = 2;
    t2->data[1][0] = 3;
    t2->data[1][1] = 4;

    NestedTuple* result = subtract_nested_tuples(t1, t2);

    if (result) {
        for (size_t i = 0; i < result->rows; i++) {
            for (size_t j = 0; j < result->cols; j++) {
                printf("%d ", result->data[i][j]);
            }
            printf("\n");
        }
        free_nested_tuple(result);
    } else {
        free_nested_tuple(t1);
        free_nested_tuple(t2);
        return 1;
    }

    free_nested_tuple(t1);
    free_nested_tuple(t2);

    return 0;
}