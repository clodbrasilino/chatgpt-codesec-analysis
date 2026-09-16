#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

Tuple* flatten_columns(Tuple **matrix, size_t rows, size_t cols) {
    if (matrix == NULL || rows == 0 || cols == 0) {
        return NULL;
    }

    Tuple *col_tuples = (Tuple *)malloc(cols * sizeof(Tuple));
    if (col_tuples == NULL) {
        return NULL;
    }

    for (size_t c = 0; c < cols; ++c) {
        col_tuples[c].size = rows;
        col_tuples[c].elements = (int *)malloc(rows * sizeof(int));
        if (col_tuples[c].elements == NULL) {
            for (size_t i = 0; i < c; ++i) {
                free(col_tuples[i].elements);
            }
            free(col_tuples);
            return NULL;
        }

        for (size_t r = 0; r < rows; ++r) {
            col_tuples[c].elements[r] = matrix[r][c].elements[0];
        }
    }

    return col_tuples;
}

void free_tuples(Tuple *tuples, size_t count) {
    if (tuples != NULL) {
        for (size_t i = 0; i < count; ++i) {
            free(tuples[i].elements);
        }
        free(tuples);
    }
}

int main(void) {
    size_t rows = 2;
    size_t cols = 3;

    Tuple **matrix = (Tuple **)malloc(rows * sizeof(Tuple *));
    if (matrix == NULL) {
        return 1;
    }

    for (size_t r = 0; r < rows; ++r) {
        matrix[r] = (Tuple *)malloc(cols * sizeof(Tuple));
        if (matrix[r] == NULL) {
            for (size_t k = 0; k < r; ++k) {
                for (size_t c = 0; c < cols; ++c) {
                    free(matrix[k][c].elements);
                }
                free(matrix[k]);
            }
            free(matrix);
            return 1;
        }
        for (size_t c = 0; c < cols; ++c) {
            matrix[r][c].size = 1;
            matrix[r][c].elements = (int *)malloc(sizeof(int));
            if (matrix[r][c].elements == NULL) {
                for (size_t k = 0; k <= r; ++k) {
                    size_t limit = (k == r) ? c : cols;
                    for (size_t j = 0; j < limit; ++j) {
                        free(matrix[k][j].elements);
                    }
                    free(matrix[k]);
                }
                free(matrix);
                return 1;
            }
            matrix[r][c].elements[0] = (int)(r * cols + c + 1);
        }
    }

    Tuple *col_tuples = flatten_columns(matrix, rows, cols);
    if (col_tuples != NULL) {
        for (size_t c = 0; c < cols; ++c) {
            printf("Column %zu: (", c);
            for (size_t r = 0; r < col_tuples[c].size; ++r) {
                printf("%d%s", col_tuples[c].elements[r], (r < col_tuples[c].size - 1) ? ", " : "");
            }
            printf(")\n");
        }
        free_tuples(col_tuples, cols);
    }

    for (size_t r = 0; r < rows; ++r) {
        for (size_t c = 0; c < cols; ++c) {
            free(matrix[r][c].elements);
        }
        free(matrix[r]);
    }
    free(matrix);

    return 0;
}