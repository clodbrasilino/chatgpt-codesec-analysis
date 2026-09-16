#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t row_size;
    size_t col_size;
} Matrix;

int compare_rows(const void *a, const void *b, size_t col_size) {
    const int *rowA = a;
    const int *rowB = b;
    int sumA = 0, sumB = 0;
    for (size_t i = 0; i < col_size; ++i) {
        sumA += rowA[i];
        sumB += rowB[i];
    }
    return (sumA > sumB) - (sumA < sumB);
}

void sort_matrix_by_row_sum(Matrix *m) {
    int (*compare_func)(const void *, const void *) = (int (*)(const void *, const void *))compare_rows;
    qsort(m->data, m->row_size, m->col_size * sizeof(int), (int (*)(const void *, const void *))compare_func);
}

Matrix create_matrix(size_t rows, size_t cols) {
    Matrix m = {0};
    m.data = (int*)malloc(rows * cols * sizeof(int));
    m.row_size = rows;
    m.col_size = cols;
    return m;
}

void free_matrix(Matrix *m) {
    free(m->data);
}

int main() {
    size_t rows = 4, cols = 3;
    Matrix m = create_matrix(rows, cols);
    m.data[0] = 10; m.data[1] = 2; m.data[2]   = 3;
    m.data[3] = 1;  m.data[4] = 5;  m.data[5]  = 9;
    m.data[6] = 4;  m.data[7] = 8;  m.data[8]  = 2;
    m.data[9] = 6;  m.data[10] = 7; m.data[11] = 11;

    sort_matrix_by_row_sum(&m);

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            printf("%d ", m.data[i * cols + j]);
        }
        printf("\n");
    }

    free_matrix(&m);
    return 0;
}