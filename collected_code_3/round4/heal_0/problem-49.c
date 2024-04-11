#include <stdio.h>

#define ROW 4
#define COL 5

void extractElements(int arr[ROW][COL], int colIndex) {
    for(int i = 0; i < ROW; i++) {
        printf("%d ", arr[i][colIndex]);
    }
    printf("\n");
}

int main() {
    int arr[ROW][COL] = {{1, 2, 3, 4, 5}, 
                         {6, 7, 8, 9, 10}, 
                         {11, 12, 13, 14, 15}, 
                         {16, 17, 18, 19, 20}};
    int colIndex = 0;
    extractElements(arr, colIndex);
    return 0;
}