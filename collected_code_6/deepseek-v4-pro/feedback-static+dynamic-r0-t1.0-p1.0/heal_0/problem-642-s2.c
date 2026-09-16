#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int **data;
    int rows;
    int cols;
} TupleMatrix;

static int rows_equal(const int *row1, const int *row2, int cols) {
    return memcmp(row1, row2, cols * sizeof(int)) == 0;
}

static void free_matrix(TupleMatrix *matrix) {
    if (matrix == NULL) {
        return;
    }
    if (matrix->data != NULL) {
        for (int i = 0; i < matrix->rows; i++) {
            free(matrix->data[i]);
            matrix->data[i] = NULL;
        }
        free(matrix->data);
        matrix->data = NULL;
    }
    matrix->rows = 0;
    matrix->cols = 0;
}

static int init_matrix(TupleMatrix *matrix, int rows, int cols) {
    if (matrix == NULL || rows <= 0 || cols <= 0) {
        return 0;
    }

    matrix->data = (int **)malloc(rows * sizeof(int *));
    if (matrix->data == NULL) {
        return 0;
    }

    for (int i = 0; i < rows; i++) {
        matrix->data[i] = (int *)malloc(cols * sizeof(int));
        if (matrix->data[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(matrix->data[j]);
                matrix->data[j] = NULL;
            }
            free(matrix->data);
            matrix->data = NULL;
            return 0;
        }
    }

    matrix->rows = rows;
    matrix->cols = cols;
    return 1;
}

static void remove_row(TupleMatrix *matrix, int row_index) {
    if (matrix == NULL || row_index < 0 || row_index >= matrix->rows) {
        return;
    }

    free(matrix->data[row_index]);
    matrix->data[row_index] = NULL;

    for (int i = row_index; i < matrix->rows - 1; i++) {
        matrix->data[i] = matrix->data[i + 1];
    }
    matrix->data[matrix->rows - 1] = NULL;
    matrix->rows--;
}

void remove_similar_rows(TupleMatrix *matrix) {
    if (matrix == NULL || matrix->data == NULL || matrix->rows <= 0 || matrix->cols <= 0) {
        return;
    }

    int i = 0;
    while (i < matrix->rows) {
        int j = i + 1;
        while (j < matrix->rows) {
            if (rows_equal(matrix->data[i], matrix->data[j], matrix->cols)) {
                remove_row(matrix, j);
            } else {
                j++;
            }
        }
        i++;
    }
}

int main(void) {
    TupleMatrix matrix;
    int rows = 5;
    int cols = 3;

    if (!init_matrix(&matrix, rows, cols)) {
        fprintf(stderr, "Failed to allocate matrix\n");
        return 1;
    }

    int test_data[5][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {1, 2, 3},
        {7, 8, 9},
        {4, 5, 6}
    };

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix.data[i][j] = test_data[i][j];
        }
    }

    printf("Original matrix (%dx%d):\n", matrix.rows, matrix.cols);
    for (int i = 0; i < matrix.rows; i++) {
        for (int j = 0; j < matrix.cols; j++) {
            printf("%d ", matrix.data[i][j]);
        }
        printf("\n");
    }

    remove_similar_rows(&matrix);

    printf("\nAfter removing similar rows (%dx%d):\n", matrix.rows, matrix.cols);
    for (int i = 0; i < matrix.rows; i++) {
        for (int j = 0; j < matrix.cols; j++) {
            printf("%d ", matrix.data[i][j]);
        }
        printf("\n");
    }

    free_matrix(&matrix);
    return 0;
}