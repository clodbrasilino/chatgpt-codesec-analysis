#include <stdio.h>

#define ROW 3
#define COL 3

void extractEven(int arr[ROW][COL]) {
    int i, j;
    for(i = 0; i < ROW; i++) {
        for(j = 0; j < COL; j++) {
            if(arr[i][j] % 2 == 0) {
                printf("%d ", arr[i][j]);
            }
        }
    }
}

int main() {
    int arr[ROW][COL] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    extractEven(arr);
    return 0;
}