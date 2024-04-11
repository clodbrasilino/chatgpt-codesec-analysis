#include <stdio.h>
#include <stdlib.h>

#define ROW 4
#define COL 5

void removeColumn(int arr[ROW][COL], int colToRemove) {
    int i, j;
    for (i = 0; i < ROW; i++) {
        for (j = colToRemove; j < COL - 1; j++) {
            arr[i][j] = arr[i][j + 1];
        }
    }
}

void printArray(int arr[ROW][COL]) {
    int i, j;
    for (i = 0; i < ROW; i++) {
        for (j = 0; j < COL - 1; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int arr[ROW][COL] = {
        {1, 2, 3, 4, 5},
        {6, 7, 8, 9, 10},
        {11, 12, 13, 14, 15},
        {16, 17, 18, 19, 20}
    };

    int colToRemove = 2;

    removeColumn(arr, colToRemove);
    printArray(arr);

    return 0;
}