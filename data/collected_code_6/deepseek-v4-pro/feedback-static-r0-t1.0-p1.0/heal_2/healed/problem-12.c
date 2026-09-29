#include <stdio.h>
#include <stdlib.h>

int row_sum(const int *row, int cols) {
    int sum = 0;
    for (int j = 0; j < cols; j++) {
        sum += row[j];
    }
    return sum;
}

int compare_rows(const void *a, const void *b, void *arg) {
    int cols = *(int *)arg;
    const int *row_a = (const int *)a;
    const int *row_b = (const int *)b;
    
    int sum_a = row_sum(row_a, cols);
    int sum_b = row_sum(row_b, cols);
    
    return sum_a - sum_b;
}

void sort_matrix_by_row_sum(int *matrix, int rows, int cols) {
    if (matrix == NULL || rows <= 0 || cols <= 0) {
        return;
    }
    
    qsort_r(matrix, rows, cols * sizeof(int), compare_rows, &cols);
}

void print_matrix(const int *matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i * cols + j]);
        }
        printf("\n");
    }
}

int main(void) {
    int rows = 3;
    int cols = 3;
    int matrix[] = {
        3, 2, 1,
        9, 8, 7,
        5, 4, 6
    };
    
    printf("Original matrix:\n");
    print_matrix(matrix, rows, cols);
    
    sort_matrix_by_row_sum(matrix, rows, cols);
    
    printf("Sorted matrix by row sum:\n");
    print_matrix(matrix, rows, cols);
    
    return 0;
}