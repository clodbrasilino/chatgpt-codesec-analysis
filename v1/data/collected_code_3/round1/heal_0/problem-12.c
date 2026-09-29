#include <stdio.h>
#include <stdlib.h>

#define ROW 3
#define COL 3

void swap(int *xp, int *yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void sort(int arr[ROW][COL]) {
    int sum[ROW] = { 0 };
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            sum[i] += arr[i][j];
        }
    }

    for (int i = 0; i < ROW - 1; i++) {
        for (int j = 0; j < ROW - i - 1; j++) {
            if (sum[j] > sum[j + 1]) {
                swap(&sum[j], &sum[j + 1]);
                for (int k = 0; k < COL; k++) {
                    swap(&arr[j][k], &arr[j + 1][k]);
                }
            }
        }
    }
}

void printMatrix(int arr[ROW][COL]) {
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int arr[ROW][COL] = { {9, 8, 7}, {2, 3, 4}, {5, 6, 1} };
    sort(arr);
    printMatrix(arr);
    return 0;
}