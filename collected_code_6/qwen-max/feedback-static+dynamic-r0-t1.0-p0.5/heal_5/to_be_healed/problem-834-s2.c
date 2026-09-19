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
             * ASan: heap-buffer-overflow (AFL crash: id:000002,sig:06,src:000000,time:865,execs:361,op:havoc,rep:6)
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
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000000,time:85,execs:42,op:havoc,rep:3; likely memory-safety defect
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
            /* Possible weaknesses found:
             * ASan: SEGV (AFL crash: id:000001,sig:06,src:000000,time:205,execs:100,op:havoc,rep:4)
             * UBSan: load of misaligned address 0x000200000001 for type 'int', which requires 4 byte alignment (AFL crash: id:000001,sig:06,src:000000,time:205,execs:100,op:havoc,rep:4)
             */
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