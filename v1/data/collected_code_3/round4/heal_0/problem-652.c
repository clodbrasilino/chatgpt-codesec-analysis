#include <stdio.h>

#define ROW 3
#define COL 4

void flattenMatrix(int matrix[ROW][COL], int tupleList[COL][ROW]) {
    for (int i = 0; i < COL; i++) {
        for (int j = 0; j < ROW; j++) {
            tupleList[i][j] = matrix[j][i];
        }
    }
}

int main() {
    int matrix[ROW][COL] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
    int tupleList[COL][ROW];

    flattenMatrix(matrix, tupleList);

    for (int i = 0; i < COL; i++) {
        printf("(");
        for (int j = 0; j < ROW; j++) {
            printf("%d", tupleList[i][j]);
            if (j < ROW - 1) {
                printf(", ");
            }
        }
        printf(")\n");
    }

    return 0;
}