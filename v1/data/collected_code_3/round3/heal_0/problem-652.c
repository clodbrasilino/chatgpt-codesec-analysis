#include <stdio.h>

#define ROW 3
#define COL 4

void flattenMatrix(int matrix[ROW][COL], int *result) {
    int i, j;
    for (i = 0; i < COL; i++) {
        for (j = 0; j < ROW; j++) {
            result[i * ROW + j] = matrix[j][i];
        }
    }
}

int main() {
    int matrix[ROW][COL] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
    int result[ROW * COL];
    flattenMatrix(matrix, result);

    int i;
    for (i = 0; i < ROW * COL; i++) {
        printf("%d ", result[i]);
    }

    return 0;
}