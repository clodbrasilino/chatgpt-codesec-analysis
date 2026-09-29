#include <stdio.h>

#define ROW 3
#define COL 4

void flattenMatrix(int matrix[ROW][COL], int rows, int cols) {
    int i, j;
    for (j = 0; j < cols; j++) {
        printf("(");
        for (i = 0; i < rows; i++) {
            printf("%d", matrix[i][j]);
            if (i < rows - 1) {
                printf(", ");
            }
        }
        printf(")");
        if (j < cols - 1) {
            printf(", ");
        }
    }
}

int main() {
    int matrix[ROW][COL] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
    flattenMatrix(matrix, ROW, COL);
    return 0;
}