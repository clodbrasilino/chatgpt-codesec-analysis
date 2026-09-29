#include <stdio.h>
#include <stdlib.h>

int** create_matrix(int rows, int cols, int* data) {
    int **matrix = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(cols * sizeof(int));
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = data[i * cols + j];
        }
    }
    return matrix;
}

void destroy_matrix(int** matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int sum_row(int* row, int cols) {
    int sum = 0;
    for (int i = 0; i < cols; i++) {
        sum += row[i];
    }
    return sum;
}

void sort_matrix_by_row_sum(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows - 1; i++) {
        for (int j = i + 1; j < rows; j++) {
            if (sum_row(matrix[i], cols) > sum_row(matrix[j], cols)) {
                int* temp = matrix[i];
                matrix[i] = matrix[j];
                matrix[j] = temp;
            }
        }
    }
}

void print_matrix(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int data[] = {3, 2, 1, 8, 7, 6, 5, 4, 9};
    int rows = 3;
    int cols = 3;

    int** matrix = create_matrix(rows, cols, data);

    printf("Original Matrix:\n");
    print_matrix(matrix, rows, cols);

    sort_matrix_by_row_sum(matrix, rows, cols);

    printf("\nSorted Matrix by Row Sum:\n");
    print_matrix(matrix, rows, cols);

    destroy_matrix(matrix, rows);
    return 0;
}