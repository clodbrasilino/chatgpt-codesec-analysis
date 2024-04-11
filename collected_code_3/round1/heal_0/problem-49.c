#include <stdio.h>

#define ROW 4
#define COL 5

void extractElement(int arr[ROW][COL], int n) {
    for(int i = 0; i < ROW; i++) {
        printf("%d ", arr[i][n]);
    }
    printf("\n");
}

int main() {
    int arr[ROW][COL] = {{1, 2, 3, 4, 5}, 
                         {6, 7, 8, 9, 10}, 
                         {11, 12, 13, 14, 15}, 
                         {16, 17, 18, 19, 20}};
    int n = 0;
    extractElement(arr, n);
    return 0;
}