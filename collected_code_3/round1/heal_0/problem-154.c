#include <stdio.h>

#define ROW 4
#define COL 5

void extractElements(int arr[ROW][COL], int n, int m, int k) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if((j+1) % k == 0) {
                printf("%d ", arr[i][j]);
            }
        }
    }
}

int main() {
    int arr[ROW][COL] = {{1, 2, 3, 4, 5}, {6, 7, 8, 9, 10}, {11, 12, 13, 14, 15}, {16, 17, 18, 19, 20}};
    int k = 2;
    extractElements(arr, ROW, COL, k);
    return 0;
}