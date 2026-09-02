#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  expected 'int **' but argument is of type 'int (*)[3]'
 */
int **extract_elements(int **matrix, int rows, int cols, int step);

int main() {
    int matrix[][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int rows = 3;
    int cols = 3;
    int step = 2;

    /* Possible weaknesses found:
     *  Assignment 'result=extract_elements(matrix,rows,cols,step)', assigned value is 0
     *  passing argument 1 of 'extract_elements' from incompatible pointer type [-Wincompatible-pointer-types]
     *  Calling function 'extract_elements' returns 0
     */
    int **result = extract_elements(matrix, rows, cols, step);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols / step; ++j) {
            /* Possible weaknesses found:
             *  Null pointer dereference: result [nullPointer]
             *  Null pointer dereference
             */
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < rows; ++i) {
        /* Possible weaknesses found:
         *  Null pointer dereference: result [nullPointer]
         *  Null pointer dereference
         */
        free(result[i]);
    }
    free(result);

    return 0;
}

int **extract_elements(int **matrix, int rows, int cols, int step) {
    if (step <= 0 || cols % step != 0) {
        return NULL;
    }

    int new_cols = cols / step;
    int **result = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; ++i) {
        result[i] = (int *)malloc(new_cols * sizeof(int));
        for (int j = 0, k = 0; j < cols; j += step, ++k) {
            result[i][k] = matrix[i][j];
        }
    }

    return result;
}