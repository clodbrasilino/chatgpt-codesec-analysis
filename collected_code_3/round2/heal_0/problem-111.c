#include <stdio.h>

#define ROW 3
#define COL 3

void findCommon(int arr1[ROW][COL], int arr2[ROW][COL]) {
    int i, j, k, l;

    for (i = 0; i < ROW; i++) {
        for (j = 0; j < COL; j++) {
            for (k = 0; k < ROW; k++) {
                for (l = 0; l < COL; l++) {
                    if (arr1[i][j] == arr2[k][l]) {
                        printf("%d ", arr1[i][j]);
                    }
                }
            }
        }
    }
}

int main() {
    int arr1[ROW][COL] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int arr2[ROW][COL] = {{7, 2, 10}, {4, 11, 12}, {13, 14, 15}};

    printf("Common elements are: ");
    findCommon(arr1, arr2);

    return 0;
}