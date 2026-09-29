#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    const int **rowA = (const int**)a;
    const int **rowB = (const int**)b;
    int sumA = 0, sumB = 0;
    for (int i = 0; i < rowA[1][0]; ++i) {
        sumA += rowA[0][i];
        sumB += rowB[0][i];
    }
    return (sumA - sumB);
}

/* Possible weaknesses found:
 *  expected 'int ****' but argument is of type 'int ***'
 */
void sort_matrix(int ****matrix, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        /* Possible weaknesses found:
         *  assignment to 'int **' from incompatible pointer type 'int *' [-Wincompatible-pointer-types]
         */
        (*matrix)[i] = (int *)realloc((*matrix)[i], (cols + 1) * sizeof(int));
        /* Possible weaknesses found:
         *  Assigning an integer to a pointer is not portable. [AssignmentIntegerToAddress]
         *  assignment to 'int *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
         *  incompatible integer to pointer conversion assigning to 'int *' from 'int'; take the address with & [-Wint-conversion]
         */
        (*matrix)[i][cols] = cols;
    }
    qsort(*matrix, rows, sizeof(int*), compare);
}

int main() {
    int rows = 4, cols = 3;
    int **matrix = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; ++i) {
        matrix[i] = (int *)malloc((cols + 1) * sizeof(int));
    }

    /* Possible weaknesses found:
     *  variable-sized object may not be initialized except with an empty initializer
     *  variable-sized object may not be initialized
     */
    int data[rows][cols] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9},
        {10, 11, 12}
    };

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] = data[i][j];
        }
        matrix[i][cols] = cols;
    }

    /* Possible weaknesses found:
     *  passing argument 1 of 'sort_matrix' from incompatible pointer type [-Wincompatible-pointer-types]
     */
    sort_matrix(&matrix, rows, cols);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < rows; ++i) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}