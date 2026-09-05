#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
} Row;

typedef struct {
    Row *rows;
    int size;
} Matrix;

Matrix remove_column(Matrix matrix, int col) {
    Matrix result;
    result.rows = NULL;
    result.size = 0;

    if (col < 0 || matrix.size == 0) {
        return result;
    }

    result.rows = (Row *)malloc(matrix.size * sizeof(Row));
    if (result.rows == NULL) {
        return result;
    }
    result.size = matrix.size;

    for (int i = 0; i < matrix.size; i++) {
        if (col >= matrix.rows[i].size) {
            result.rows[i].data = NULL;
            result.rows[i].size = 0;
            continue;
        }

        int new_size = matrix.rows[i].size - 1;
        if (new_size == 0) {
            result.rows[i].data = NULL;
            result.rows[i].size = 0;
        } else {
            result.rows[i].data = (int *)malloc(new_size * sizeof(int));
            if (result.rows[i].data == NULL) {
                for (int j = 0; j < i; j++) {
                    free(result.rows[j].data);
                }
                free(result.rows);
                result.rows = NULL;
                result.size = 0;
                return result;
            }
            result.rows[i].size = new_size;

            for (int j = 0, k = 0; j < matrix.rows[i].size; j++) {
                if (j != col) {
                    result.rows[i].data[k++] = matrix.rows[i].data[j];
                }
            }
        }
    }

    return result;
}

void free_matrix(Matrix matrix) {
    for (int i = 0; i < matrix.size; i++) {
        free(matrix.rows[i].data);
    }
    free(matrix.rows);
}

int main() {
    Matrix matrix;
    matrix.size = 3;
    matrix.rows = (Row *)malloc(matrix.size * sizeof(Row));

    int row0[] = {1, 2, 3};
    int row1[] = {4, 5, 6};
    int row2[] = {7, 8, 9};

    matrix.rows[0].data = row0;
    matrix.rows[0].size = 3;
    matrix.rows[1].data = row1;
    matrix.rows[1].size = 3;
    matrix.rows[2].data = row2;
    matrix.rows[2].size = 3;

    Matrix result = remove_column(matrix, 1);

    for (int i = 0; i < result.size; i++) {
        for (int j = 0; j < result.rows[i].size; j++) {
            printf("%d ", result.rows[i].data[j]);
        }
        printf("\n");
    }

    free_matrix(result);
    free(matrix.rows);

    return 0;
}