#include <stdio.h>
#include <stdlib.h>

typedef int Tuple;
typedef Tuple* TupleList;

TupleList create_tuple_list(int size) {
    return (TupleList)malloc(size * sizeof(Tuple));
}

void free_tuple_list(TupleList list) {
    free(list);
}

int** create_matrix(int rows, int cols) {
    int** matrix = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; ++i) {
        matrix[i] = (int*)malloc(cols * sizeof(int));
    }
    return matrix;
}

void free_matrix(int** matrix, int rows) {
    for (int i = 0; i < rows; ++i) {
        free(matrix[i]);
    }
    free(matrix);
}

int get_column_count(int** matrix, int rows) {
    return matrix[0] ? sizeof(matrix[0]) / sizeof(matrix[0][0]) : 0;
}

void flatten_matrix_to_tuples(int** matrix, int rows, TupleList* result, int* result_size) {
    int cols = get_column_count(matrix, rows);
    *result = create_tuple_list(rows * cols);
    *result_size = 0;
    for (int col = 0; col < cols; ++col) {
        for (int row = 0; row < rows; ++row) {
            (*result)[(*result_size)++] = matrix[row][col];
        }
    }
}

int main() {
    int rows = 3;
    int cols = 4;
    int** matrix = create_matrix(rows, cols);

    // Fill the matrix with some values
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] = i * cols + j;
        }
    }

    TupleList result = NULL;
    int result_size = 0;
    flatten_matrix_to_tuples(matrix, rows, &result, &result_size);

    // Print the flattened tuple list
    for (int i = 0; i < result_size; ++i) {
        printf("%d ", result[i]);
    }
    printf("\n");

    free_tuple_list(result);
    free_matrix(matrix, rows);

    return 0;
}