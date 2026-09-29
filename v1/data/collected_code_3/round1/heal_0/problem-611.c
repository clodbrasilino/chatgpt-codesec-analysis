#include <stdio.h>

#define ROW 5
#define COL 3

int findMaxInColumn(int arr[ROW][COL], int n) {
    int max = arr[0][n];
    for (int i = 1; i < ROW; i++) {
        if (arr[i][n] > max) {
            max = arr[i][n];
        }
    }
    return max;
}

int main() {
    int arr[ROW][COL] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12}, {13, 14, 15}};
    int n = 1;
    int max = findMaxInColumn(arr, n);
    printf("Maximum of column %d is %d\n", n, max);
    return 0;
}