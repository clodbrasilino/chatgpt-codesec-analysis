#include <stdio.h>
#include <stdlib.h>

int compare_rows(const void *a, const void *b, void *context) {
    int cols = *(int *)context;
    const int *row_a = (const int *)a;
    const int *row_b = (const int *)b;
    int sum_a = 0, sum_b = 0;
    for (int i = 0; i < cols; i++) {
        sum_a += row_a[i];
        sum_b += row_b[i];
    }
    if (sum_a < sum_b) return -1;
    if (sum_a > sum_b) return 1;
    return 0;
}

void sort_matrix_by_row_sum(int *matrix, int rows, int cols) {
    if (matrix == NULL || rows <= 0 || cols <= 0) {
        return;
    }
    size_t row_size = cols * sizeof(int);
    void *temp_row = malloc(row_size);
    if (temp_row == NULL) {
        return;
    }

    for (int i = 0; i < rows - 1; i++) {
        for (int j = 0; j < rows - i - 1; j++) {
            int *row_a = matrix + j * cols;
            int *row_b = matrix + (j + 1) * cols;
            int sum_a = 0, sum_b = 0;
            for (int k = 0; k < cols; k++) {
                sum_a += row_a[k];
                sum_b += row_b[k];
            }
            if (sum_a > sum_b) {
                for (int k = 0; k < cols; k++) {
                    ((int *)temp_row)[k] = row_a[k];
                    row_a[k] = row_b[k];
                    row_b[k] = ((int *)temp_row)[k];
                }
            }
        }
    }

    free(temp_row);
}

int main(void) {
    int matrix[3][3] = {
        {3, 4, 5},
        {1, 1, 1},
        {2, 2, 2}
    };
    int rows = 3;
    int cols = 3;

    sort_matrix_by_row_sum(&matrix[0][0], rows, cols);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}