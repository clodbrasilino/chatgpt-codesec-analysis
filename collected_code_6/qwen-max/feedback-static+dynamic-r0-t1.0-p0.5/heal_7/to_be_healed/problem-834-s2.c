#include <stdio.h>
#include <stdlib.h>

void fillSpiralMatrix(int n, int matrix[n][n]) {
    int val = 1;
    int layer = 0;
    while (layer < n / 2) {
        for (int i = layer; i < n - layer; ++i) {
            matrix[layer][i] = val++;
        }
        for (int i = layer + 1; i < n - layer; ++i) {
            /* Possible weaknesses found:
             * ASan: heap-buffer-overflow (AFL crash: id:000004,sig:11,src:000001,time:13050,execs:424,op:quick,pos:5)
             */
            matrix[i][n - layer - 1] = val++;
        }
        for (int i = n - layer - 2; i >= layer; --i) {
            matrix[n - layer - 1][i] = val++;
        }
        for (int i = n - layer - 2; i > layer; --i) {
            matrix[i][layer] = val++;
        }
        layer++;
    }
    if (n % 2 != 0) {
        matrix[n / 2][n / 2] = val;
    }
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000000,time:303,execs:139,op:havoc,rep:8; likely memory-safety defect
  */

int main() {
    int n;
    printf("Enter the size of the matrix: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        return 1;
    }

    int **matrix = malloc(n * sizeof(int *));
    for (int i = 0; i < n; ++i) {
        matrix[i] = malloc(n * sizeof(int));
    }

    fillSpiralMatrix(n, (int (*)[n])matrix);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%4d", matrix[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < n; ++i) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}