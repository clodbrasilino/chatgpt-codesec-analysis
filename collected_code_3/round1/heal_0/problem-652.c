#include <stdio.h>

#define ROW 3
#define COL 3

void flattenMatrix(int matrix[ROW][COL], int n, int m) {
    int i, j;
    for (j = 0; j < m; j++) {
        printf("(");
        for (i = 0; i < n; i++) {
            printf("%d", matrix[i][j]);
            if (i < n - 1) {
                printf(", ");
            }
        }
        printf(")");
        if (j < m - 1) {
            printf(", ");
        }
    }
}

int main() {
    int matrix[ROW][COL] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    flattenMatrix(matrix, ROW, COL);
    return 0;
}