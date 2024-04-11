#include <stdio.h>

#define ROW 4
#define COL 5

void extractElements(int arr[ROW][COL], int index) {
    for (int i = 0; i < ROW; i++) {
        printf("%d ", arr[i][index]);
    }
    printf("\n");
}

int main() {
    int arr[ROW][COL] = {
        {1, 2, 3, 4, 5},
        {6, 7, 8, 9, 10},
        {11, 12, 13, 14, 15},
        {16, 17, 18, 19, 20}
    };

    int index = 0;
    extractElements(arr, index);

    return 0;
}