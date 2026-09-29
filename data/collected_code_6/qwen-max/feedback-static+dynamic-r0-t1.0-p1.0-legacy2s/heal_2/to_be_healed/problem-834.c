#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  expected 'int * (*)[n]' but argument is of type 'int (*)[n]'
 */
void fillSpiralMatrix(int n, int *matrix[n][n]) {
    int value = 1;
    int layer = 0;
    while (value <= n * n) {
        for (int i = layer; i < n - layer; i++) {
            /* Possible weaknesses found:
             *  incompatible integer to pointer conversion assigning to 'int *' from 'int' [-Wint-conversion]
             *  Assigning an integer to a pointer is not portable. [AssignmentIntegerToAddress]
             *  assignment to 'int *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
             */
            (*matrix)[layer * n + i] = value++;
        }
        for (int i = layer + 1; i < n - layer; i++) {
            /* Possible weaknesses found:
             *  incompatible integer to pointer conversion assigning to 'int *' from 'int' [-Wint-conversion]
             *  Assigning an integer to a pointer is not portable. [AssignmentIntegerToAddress]
             *  assignment to 'int *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
             */
            (*matrix)[i * n + n - layer - 1] = value++;
        }
        for (int i = n - layer - 2; i >= layer; i--) {
            if (layer < n - layer - 1) {
                /* Possible weaknesses found:
                 *  incompatible integer to pointer conversion assigning to 'int *' from 'int' [-Wint-conversion]
                 *  Assigning an integer to a pointer is not portable. [AssignmentIntegerToAddress]
                 *  assignment to 'int *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
                 */
                (*matrix)[(n - layer - 1) * n + i] = value++;
            }
        }
        for (int i = n - layer - 2; i > layer; i--) {
            /* Possible weaknesses found:
             *  incompatible integer to pointer conversion assigning to 'int *' from 'int' [-Wint-conversion]
             *  Assigning an integer to a pointer is not portable. [AssignmentIntegerToAddress]
             *  assignment to 'int *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
             */
            (*matrix)[i * n + layer] = value++;
        }
        layer++;
    }
}

int main() {
    int n;
    printf("Enter the size of the matrix: ");
    scanf("%d", &n);
    if (n < 1) {
        return 1;
    }

    int **matrix = malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        matrix[i] = malloc(n * sizeof(int));
    }

    /* Possible weaknesses found:
     *  passing argument 2 of 'fillSpiralMatrix' from incompatible pointer type [-Wincompatible-pointer-types]
     */
    fillSpiralMatrix(n, (int(*)[n])matrix);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%4d", matrix[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}