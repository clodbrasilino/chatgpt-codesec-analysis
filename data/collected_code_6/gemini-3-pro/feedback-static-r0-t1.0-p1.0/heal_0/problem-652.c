#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} Tuple;

Tuple** flatten_tuple_matrix(Tuple*** matrix, int rows, int cols) {
    if (matrix == NULL || rows <= 0 || cols <= 0) {
        return NULL;
    }

    Tuple** flattened = (Tuple**)malloc(cols * sizeof(Tuple*));
    if (flattened == NULL) {
        return NULL;
    }

    for (int i = 0; i < cols; i++) {
        flattened[i] = (Tuple*)malloc(rows * sizeof(Tuple));
        if (flattened[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(flattened[j]);
            }
            free(flattened);
            return NULL;
        }
    }

    for (int i = 0; i < rows; i++) {
        if (matrix[i] == NULL) {
            for (int k = 0; k < cols; k++) {
                free(flattened[k]);
            }
            free(flattened);
            return NULL;
        }
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] != NULL) {
                flattened[j][i].x = matrix[i][j]->x;
                flattened[j][i].y = matrix[i][j]->y;
            } else {
                flattened[j][i].x = 0;
                flattened[j][i].y = 0;
            }
        }
    }

    return flattened;
}

int main(void) {
    int rows = 2;
    int cols = 3;

    Tuple*** matrix = (Tuple***)malloc(rows * sizeof(Tuple**));
    if (matrix == NULL) return 1;

    for (int i = 0; i < rows; i++) {
        matrix[i] = (Tuple**)malloc(cols * sizeof(Tuple*));
        if (matrix[i] == NULL) {
            for (int j = 0; j < i; j++) free(matrix[j]);
            free(matrix);
            return 1;
        }
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = (Tuple*)malloc(sizeof(Tuple));
            if (matrix[i][j] == NULL) {
                for (int k = 0; k < j; k++) free(matrix[i][k]);
                free(matrix[i]);
                for (int m = 0; m < i; m++) {
                    for (int n = 0; n < cols; n++) free(matrix[m][n]);
                    free(matrix[m]);
                }
                free(matrix);
                return 1;
            }
            matrix[i][j]->x = i * 10 + j;
            matrix[i][j]->y = (i * 10 + j) + 1;
        }
    }

    Tuple** flattened = flatten_tuple_matrix(matrix, rows, cols);

    if (flattened != NULL) {
        for (int j = 0; j < cols; j++) {
            for (int i = 0; i < rows; i++) {
                printf("(%d, %d) ", flattened[j][i].x, flattened[j][i].y);
            }
            printf("\n");
        }
    }

    if (flattened != NULL) {
        for (int j = 0; j < cols; j++) {
            free(flattened[j]);
        }
        free(flattened);
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            free(matrix[i][j]);
        }
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}